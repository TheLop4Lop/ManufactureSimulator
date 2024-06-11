// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "CharacterController.h"
#include "BaseMachinery.h"
#include "BaseComputer.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterController = Cast<ACharacterController>(GetController());
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Checks if the controller isn't nullptr and if there's a actor in Character sight
	if(InSightLine() != nullptr && DoOnceWidget)
	{
		AActor* ActorInSight = InSightLine();
		if(ActorInSight->IsA(ABaseComputer::StaticClass()))
		{
			Computer = Cast<ABaseComputer>(ActorInSight);
			ComputerMachine = nullptr;
		}else if(ActorInSight->IsA(ABaseMachinery::StaticClass()))
		{
			ComputerMachine = Cast<ABaseMachinery>(ActorInSight);
			Computer = nullptr;
		}
		
		InteractionWidget = CreateWidget(CharacterController, InteractionWidgetClass);
		if(InteractionWidget != nullptr)
		{
			InteractionWidget->AddToViewport();
		}
		DoOnceWidget = false;
	}else if(InSightLine() == nullptr && !DoOnceWidget)
	{
		InteractionWidget->RemoveFromParent();
		DoOnceWidget = true;
	}

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction(TEXT("Interaction"), EInputEvent::IE_Released, this, &ABaseCharacter::Interaction);

}

///////////////////////////////////// BASE CHARACTER CONFIGURATION ////////////////////////////////
// Section to declare all configuration into Character.

// Move character forward method.
void ABaseCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);

}

// Move character right method.
void ABaseCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);

}

///////////////////////////////////// OBJECT INTERACTION ////////////////////////////////
// Interaction object section.

// Checks if there's an actor in front of the character.
AActor* ABaseCharacter::InSightLine()
{
	FVector SightLocation;
	FRotator SightRotation;
	FVector SightEndVector;

	if(CharacterController != nullptr)
	{
		CharacterController->GetPlayerViewPoint(SightLocation, SightRotation);
		SightEndVector = SightLocation + (SightRotation.Vector() * ObjectRangeSight);
	}

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(5.f);

	if(GetWorld()->SweepSingleByChannel(Hit, SightLocation, SightEndVector, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, Sphere, Params))
	{
		return Hit.GetActor();

	}

	return nullptr;

}

// Method that interacts directly with the object displaying widget.
void ABaseCharacter::Interaction()
{
	if(!DoOnceWidget)
	{
		if(CharacterController != nullptr && Computer != nullptr && Computer->GetComputerWidgetClass() != nullptr)
		{
			Computer->AddWidgetFromComputer(CharacterController);
			CharacterController->SetMovement(true);

		}else if(CharacterController != nullptr && ComputerMachine != nullptr && ComputerMachine->GetComputerWidgetClass() != nullptr)
		{
			ComputerMachine->AddWidgetFromComputer(CharacterController);
			CharacterController->SetMovement(true);

		}
	}

}






void ABaseCharacter::ResetMoveInput()
{
	UE_LOG(LogTemp, Display, TEXT("EXIT"));

}