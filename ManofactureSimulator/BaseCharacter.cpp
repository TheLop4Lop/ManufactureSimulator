// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "CharacterController.h"
#include "Interactable.h"
#include "BaseComputer.h"
#include "BaseCanister.h"
#include "BaseProduct.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	holdComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Hold Position"));
	holdComponent->SetupAttachment(RootComponent);

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

	AActor* actorInSight = InSightLine().GetActor();
	UPrimitiveComponent* HitComponent = InSightLine().GetComponent();

	//Checks if the controller isn't nullptr and if there's a actor in Character sight
	if(actorInSight != nullptr && DoOnceWidget)
	{
		if(actorInSight->IsA(ABaseComputer::StaticClass()))
		{
			Computer = Cast<ABaseComputer>(actorInSight);

			SetInteractionWidget(computerInteractionWidgetClass);
			DoOnceWidget = false;
		}else if(actorInSight->IsA(ABaseProduct::StaticClass()) || actorInSight->IsA(ABaseCanister::StaticClass()))
		{
			SetInteractionWidget(grabInteractionWidgetClass);
			DoOnceWidget = false;
		}else if(HitComponent && HitComponent->IsA(UBoxComponent::StaticClass()) && objectHolded)
		{
			SetInteractionWidget(releaseInteractionWidgetClass);
			DoOnceWidget = false;
		}

	}else if(actorInSight == nullptr && !DoOnceWidget)
	{
		if(InteractionWidget)
		{
			InteractionWidget->RemoveFromParent();
			InteractionWidget = nullptr;
		}
		DoOnceWidget = true;
	}

	UpdateHoldedObjectLocation();

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
	PlayerInputComponent->BindAction(TEXT("Grab"), EInputEvent::IE_Pressed, this, &ABaseCharacter::GrabObject);
	PlayerInputComponent->BindAction(TEXT("Release"), EInputEvent::IE_Released, this, &ABaseCharacter::ReleaseObject);

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

// Set Interaction widget to a specific WidgetClass.
void ABaseCharacter::SetInteractionWidget(TSubclassOf<class UUserWidget> widgetClass)
{
	if(widgetClass)
	{
		InteractionWidget = CreateWidget(CharacterController, widgetClass);
		if(InteractionWidget != nullptr)
		{
			InteractionWidget->AddToViewport();
		}
	}
	
}

// Checks if there's an actor in front of the character.
FHitResult ABaseCharacter::InSightLine()
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

	GetWorld()->SweepSingleByChannel(Hit, SightLocation, SightEndVector, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, Sphere, Params);
	
	return Hit;

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
		}
	}

}

// Grabs object and attach it to holdComponent.
void ABaseCharacter::GrabObject()
{
	AActor* hitActor = InSightLine().GetActor();
	if(hitActor != nullptr && (hitActor->IsA(ABaseProduct::StaticClass()) || hitActor->IsA(ABaseCanister::StaticClass())))
	objectHolded = hitActor;
	
	if(objectHolded != nullptr && objectHolded->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		IInteractable::Execute_InteractionFunctionality(objectHolded);
		objectHolded->AttachToComponent(holdComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale); /////////
	}

}

// Updates the location of object from tick.
void ABaseCharacter::UpdateHoldedObjectLocation()
{
	if(objectHolded)
	{
		objectHolded->SetActorLocation(holdComponent->GetComponentLocation());
		objectHolded->SetActorRotation(GetActorRotation());
	}

}

// Releases objecto from holdComponent.
void ABaseCharacter::ReleaseObject()
{
	if(objectHolded)
	{
		objectHolded->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform); ////////////
		releaseHold.ExecuteIfBound();
	}
	objectHolded = nullptr;

}
