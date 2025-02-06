// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonitorComputerWidget.h" // For Struct.
#include "BaseCharacter.generated.h"

DECLARE_DELEGATE(FHold);
DECLARE_DELEGATE_OneParam(FPlaceRelease, UPrimitiveComponent*);

UCLASS()
class MANOFACTURESIMULATOR_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Resets movement on character.
	void ResetMoveInput();

	// Simple release grab action.
	FHold releaseHold;

	// Complex release grab actions, with excecution also sends location.
	FPlaceRelease releaseComplexHold;

private:
	///////////////////////////////////// BASE CHARACTER CONFIGURATION ////////////////////////////////
	// Section to declare all configuration into Character.

	// Spring arm, responsable for holding the camera and pivot point.
	UPROPERTY(EditAnywhere, Category = "Character Properties", meta = (AllowPrivateAccess))
	class USpringArmComponent* SpringArm;

	// Character camera.
	UPROPERTY(EditAnywhere, Category = "Character Properties", meta = (AllowPrivateAccess))
	class UCameraComponent* Camera;

	// Move character forward method.
	void MoveForward(float AxisValue);

	// Move character right method.
	void MoveRight(float AxisValue);

	// Character controller pinter.
	class ACharacterController* CharacterController;

	///////////////////////////////////// GENERAL INTERACTION ////////////////////////////////
	// Interaction for base interaction section.

	// Range for object interaction.
	UPROPERTY(EditAnywhere, Category = "Character Properties", meta = (AllowPrivateAccess))
	float ObjectRangeSight = 100;

	// Holds the Widget Class to an specific interaction.
	UUserWidget* InteractionWidget;

	// Checks if there's an actor in front of the character.
	FHitResult InSightLine();

	// Set Interaction widget to a specific WidgetClass.
	void SetInteractionWidget(TSubclassOf<class UUserWidget> widgetClass);

	// Controls the flow of Widget added in Tick.
	bool DoOnceWidget = true;

	// Continiously check interactions on world.
	void InteractionOnSight();

	///////////////////////////////////// COMPUTER INTERACTION ////////////////////////////////
	// Interaction computer section.

	// Interaction widget.
	UPROPERTY(EditAnywhere, Category = "Computer Widgets", meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> computerInteractionWidgetClass;

	// Method that interacts directly with the object displaying widget.
	void ComputerInteraction();
	
	// Reference to computer seen by character.
	class ABaseComputer* Computer;

	// Holds value reference for an displayed widget to avoid overlapping.
	bool bIsWidgetDisplayed;

	///////////////////////////////////// GRAB INTERACTION ////////////////////////////////
	// Interaction with grabbing objects section.

	// Component responsable for holdin in place object
	UPROPERTY(EditAnywhere, Category = "Grab Properties", meta = (AllowPrivateAccess))
	USceneComponent* holdComponent;

	// Grab Interaction widget.
	UPROPERTY(EditAnywhere, Category = "Grab Widgets", meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> grabInteractionWidgetClass;

	// Release Interaction widget.
	UPROPERTY(EditAnywhere, Category = "Grab Widgets", meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> releaseInteractionWidgetClass;

	// Canister indicator widget.
	UPROPERTY(EditAnywhere, Category = "Grab Widgets", meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> canisterLevelIndicatorClass;

	// Grabs object and attach it to holdComponent.
	void GrabObject();

	// Updates the location of object from tick.
	void UpdateHoldedObjectLocation();

	// Releases objecto from holdComponent.
	void ReleaseObject();

	// Holds the Widget Class to an specific interaction.
	class UCanisterWidget* canisterWidget;

	// Holds reference to the object holded by character.
	AActor* objectHolded;

	// Holds the location of the boxComponent to place the holded object.
	UPrimitiveComponent* HitComponent;

	// Use to get values of cannister to update value on widget.
	class ABaseCanister* holdedCanister;

	// Holds value if an object can be placed on a boxComponent.
	bool canPlaceObject;

	///////////////////////////////////// GRAB INTERACTION SOUND ////////////////////////////////
	// Interaction with grabbing objects sound section.

	// Canister grab sound.
	UPROPERTY(EditAnywhere, Category = "Grab Sounds", meta = (AllowPrivateAccess))
	USoundBase* canisterGrabSound;

	// Canister grab sound.
	UPROPERTY(EditAnywhere, Category = "Grab Sounds", meta = (AllowPrivateAccess))
	USoundBase* pieceGrabSound;

	// Plays sound of grabbed object by the player.
	void PlayGrabbedObjectSound(USoundBase* grabbedObjectSound);

	///////////////////////////////////// MONITOR WIDGET PROPERTIES ////////////////////////////////
	// Interaction with grabbing objects sound section.

	// Monitor computer interaction widget.
	UPROPERTY(EditAnywhere, Category = "Monitor Widget", meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> monitorWidgetClass;

	// Holds the Widget Class to monitor computer.
	UMonitorComputerWidget* monitorWidget;

	// Set the Monitor Widget to player to see Stock information.
	void SetMonitorWidget();

	// Boolean to control flip-flop interaction on widget display.
	bool isMonitorWidgetSet;

	// Holds reference of Manager Computer in the world.
	class AManagerComputer* computerManager;

	// Get an struct array with the orders status from stock.
	void GetOrderOfTheDayStatus(TArray<FString> orders, TArray<struct FOrderOTD> ordersStatus);

	// Holds the ordes of the day.
	TArray<FString> ordersOfTheDay;

	// Hold the order status from storage.
	TArray<struct FOrderOTD> ordersOfTheDayStatus;

	///////////////////////////////////// INFORMATION SCREEN WIDGET PROPERTIES ////////////////////////////////
	// Interaction with Information Screens.

	// Information Screen interaction widget.
	UPROPERTY(EditAnywhere, Category = "Monitor Widget", meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> informationScreenWidgetClass;

	// Holds the a reference to Information Screens infront of player.
	class AInformationScreen* infoScreen;

};
