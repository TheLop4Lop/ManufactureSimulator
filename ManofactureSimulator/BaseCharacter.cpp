// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "CharacterController.h"
#include "InformationScreen.h"
#include "ManagerComputer.h"
#include "CanisterWidget.h"
#include "Interactable.h"
#include "BaseComputer.h"
#include "BaseCanister.h"
#include "BaseProduct.h"
#include "ExitDoor.h"

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
	CharacterController->resetMovement.BindUObject(this, &ABaseCharacter::ResetMoveInput);

	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AManagerComputer::StaticClass(), actorsInWorld);
	if (actorsInWorld.IsValidIndex(0))
	{
		computerManager = Cast<AManagerComputer>(actorsInWorld[0]);
		computerManager->ordersForMonitor.BindUObject(this, &ABaseCharacter::GetOrderOfTheDayStatus);
		computerManager->currentMoneyStatus.BindUObject(this, &ABaseCharacter::GetCurrentEarnings);
	}
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InteractionOnSight();
	UpdateHoldedObjectLocation();

	if(holdedCanister && canisterWidget)
	{
		canisterWidget->SetIndicatorCanisterLevel((float)holdedCanister->GetCanisterCurrentLevel()/(float)holdedCanister->GetCanisterMaxCapacity());
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

	PlayerInputComponent->BindAction(TEXT("Interaction"), EInputEvent::IE_Released, this, &ABaseCharacter::ComputerInteraction);
	PlayerInputComponent->BindAction(TEXT("Grab"), EInputEvent::IE_Pressed, this, &ABaseCharacter::GrabObject);
	PlayerInputComponent->BindAction(TEXT("Release"), EInputEvent::IE_Released, this, &ABaseCharacter::ReleaseObject);

	PlayerInputComponent->BindAction(TEXT("ShowMonitor"), EInputEvent::IE_Released, this, &ABaseCharacter::SetMonitorWidget);

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

//Resets movement on character.
void ABaseCharacter::ResetMoveInput()
{
	this->GetMovementComponent()->Activate();
	bIsWidgetDisplayed = false;

	Computer = nullptr;
	infoScreen = nullptr;

}

///////////////////////////////////// GENERAL INTERACTION ////////////////////////////////
// Interaction for base interaction section.

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

// Continiously check interactions on world.
void ABaseCharacter::InteractionOnSight()
{
	AActor* actorInSight = InSightLine().GetActor();
	UPrimitiveComponent* sightHitComponent = InSightLine().GetComponent();

	//Checks if the controller isn't nullptr and if there's a actor in Character sight
	if(actorInSight != nullptr && DoOnceWidget)
	{
		if(actorInSight->IsA(AExitDoor::StaticClass()))
		{
			exitDoor = Cast<AExitDoor>(actorInSight);
			SetInteractionWidget(exitDoorWidgetClass);
			
			canPlaceObject = false;
			DoOnceWidget = false;
		}else if(actorInSight->IsA(AInformationScreen::StaticClass())) 
		{
			infoScreen = Cast<AInformationScreen>(actorInSight);
			SetInteractionWidget(informationScreenWidgetClass);

			canPlaceObject = false;
			DoOnceWidget = false;
		}else if(actorInSight->IsA(ABaseComputer::StaticClass()))
		{
			Computer = Cast<ABaseComputer>(actorInSight);

			SetInteractionWidget(computerInteractionWidgetClass);
			canPlaceObject = false;
			DoOnceWidget = false;
		}else if(actorInSight->IsA(ABaseProduct::StaticClass()) || actorInSight->IsA(ABaseCanister::StaticClass()))
		{
			SetInteractionWidget(grabInteractionWidgetClass);
			canPlaceObject = false;
			DoOnceWidget = false;
		}else if(sightHitComponent && sightHitComponent->IsA(UBoxComponent::StaticClass()) && objectHolded)
		{
			SetInteractionWidget(releaseInteractionWidgetClass);
			HitComponent = sightHitComponent;

			canPlaceObject = true;
			DoOnceWidget = false;
		}

	}else if(actorInSight == nullptr && !DoOnceWidget)
	{
		if(InteractionWidget)
		{
			InteractionWidget->RemoveFromParent();
			InteractionWidget = nullptr;
		}
		canPlaceObject = false;
		DoOnceWidget = true;
	}

}

///////////////////////////////////// COMPUTER INTERACTION ////////////////////////////////
// Interaction computer section.

// Method that interacts directly with the object displaying widget.
void ABaseCharacter::ComputerInteraction()
{
	if(!DoOnceWidget)
	{
		if(CharacterController != nullptr && Computer != nullptr && Computer->GetComputerWidgetClass() != nullptr && !bIsWidgetDisplayed)
		{
			Computer->AddWidgetFromComputer(CharacterController);
			this->GetMovementComponent()->Deactivate();
			CharacterController->SetMovement(true);

			bIsWidgetDisplayed = true;
		}else if(CharacterController != nullptr && exitDoor != nullptr && exitDoor->GetComputerWidgetClass() != nullptr && !bIsWidgetDisplayed)
		{
			exitDoor->AddWidgetFromComputer(CharacterController);
			this->GetMovementComponent()->Deactivate();
			CharacterController->SetMovement(true);

			bIsWidgetDisplayed = true;
		}else if(CharacterController != nullptr && infoScreen != nullptr && infoScreen->GetComputerWidgetClass() != nullptr && !bIsWidgetDisplayed)
		{
			infoScreen->AddWidgetFromComputer(CharacterController);
			this->GetMovementComponent()->Deactivate();
			CharacterController->SetMovement(true);

			bIsWidgetDisplayed = true;
		}
	}

}

///////////////////////////////////// GRAB INTERACTION ////////////////////////////////
// Interaction with grabbing objects section.

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

		if(InteractionWidget != nullptr)
		{
			InteractionWidget->RemoveFromParent();
			InteractionWidget = nullptr;
		}

		if(objectHolded->IsA(ABaseCanister::StaticClass()))
		{
			PlayGrabbedObjectSound(canisterGrabSound);
			holdedCanister = Cast<ABaseCanister>(objectHolded);

			canisterWidget = Cast<UCanisterWidget>(CreateWidget(CharacterController, canisterLevelIndicatorClass));
			if(canisterWidget && holdedCanister)
			{
				canisterWidget->AddToViewport();
			}
		}else
		{
			PlayGrabbedObjectSound(pieceGrabSound);
		}
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
	if(objectHolded && !canPlaceObject)
	{
		objectHolded->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform); ////////////
		releaseHold.ExecuteIfBound();
	}else if(objectHolded && canPlaceObject)
	{
		objectHolded->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		
		UE_LOG(LogTemp, Display, TEXT("HitComponent name: %s."), *HitComponent->GetName());
		releaseComplexHold.ExecuteIfBound(HitComponent);
	}

	if(canisterWidget)
	{
		canisterWidget->RemoveFromParent();
		canisterWidget = nullptr;
		holdedCanister = nullptr;
	}

	objectHolded = nullptr;

}

///////////////////////////////////// GRAB INTERACTION SOUND ////////////////////////////////
// Interaction with grabbing objects sound section.

// Plays sound of grabbed object by the player.
void ABaseCharacter::PlayGrabbedObjectSound(USoundBase* grabbedObjectSound)
{
	if(grabbedObjectSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), grabbedObjectSound, holdComponent->GetComponentLocation());
	}

}

///////////////////////////////////// MONITOR WIDGET PROPERTIES ////////////////////////////////
// Interaction with grabbing objects sound section.

// Set the Monitor Widget to player to see Stock information.
void ABaseCharacter::SetMonitorWidget()
{
	if(monitorWidgetClass && CharacterController)
	{
		if(!isMonitorWidgetSet)
		{
			monitorWidget = Cast<UMonitorComputerWidget>(CreateWidget(CharacterController, monitorWidgetClass));
			if(monitorWidget)
			{
				monitorWidget->AddToViewport();
				isMonitorWidgetSet = true;
				monitorWidget->SetEarnings(currentEarings);
				if(ordersOfTheDay.Num() > 0 && ordersOfTheDayStatus.Num() > 0)
				{
					UE_LOG(LogTemp, Display, TEXT("ordersOfTheDay: %i. ordersOfTheDayStatus: %i."), ordersOfTheDay.Num(), ordersOfTheDayStatus.Num());
					monitorWidget->SetOrderOTDsStatus(ordersOfTheDay, ordersOfTheDayStatus);
				}
			}
		}else
		{
			monitorWidget->RemoveFromParent();
			monitorWidget = nullptr;
			isMonitorWidgetSet = false;
		}
	}

}

// Get an struct array with the orders status from stock.
void ABaseCharacter::GetOrderOfTheDayStatus(TArray<FString> orders, TArray<FOrderOTD> ordersStatus)
{
	ordersOfTheDay.Empty();
	ordersOfTheDayStatus.Empty();
	for(int i = 0; i < orders.Num(); i++)
	{
		ordersOfTheDay.Add(orders[i]);
		ordersOfTheDayStatus.Add(ordersStatus[i]);
		UE_LOG(LogTemp, Display, TEXT("TOTAL ORDER STATUS: %i"), ordersOfTheDayStatus[i].canProduceByStock);
	}

}

// Get The current earning to be displayed on Monitor.
void ABaseCharacter::GetCurrentEarnings(float earnigns)
{
	currentEarings = earnigns;
	if(monitorWidget)
	{
		monitorWidget->SetEarnings(currentEarings);
	}

}
