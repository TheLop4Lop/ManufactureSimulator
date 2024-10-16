// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

	// Character controller pinter.
	class ACharacterController* CharacterController;

	// Move character forward method.
	void MoveForward(float AxisValue);
	// Move character right method.
	void MoveRight(float AxisValue);

	///////////////////////////////////// OBJECT INTERACTION ////////////////////////////////
	// Interaction object section.

	// Interaction widget.
	UPROPERTY(EditAnywhere, Category = "Widgets", meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> computerInteractionWidgetClass;

	// Interaction widget.
	UPROPERTY(EditAnywhere, Category = "Widgets", meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> grabInteractionWidgetClass;

	// Interaction widget.
	UPROPERTY(EditAnywhere, Category = "Widgets", meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> releaseInteractionWidgetClass;

	// Holds the Widget Class to an specific interaction.
	UUserWidget* InteractionWidget;

	// Set Interaction widget to a specific WidgetClass.
	void SetInteractionWidget(TSubclassOf<class UUserWidget> widgetClass);

	// Range for object interaction.
	UPROPERTY(EditAnywhere, Category = "Character Properties", meta = (AllowPrivateAccess))
	float ObjectRangeSight = 100;
	
	// Checks if there's an actor in front of the character.
	FHitResult InSightLine();
	bool DoOnceWidget = true;

	// Method that interacts directly with the object displaying widget.
	void Interaction();
	
	class ABaseComputer* Computer;

	// Component responsable for holdin in place object
	UPROPERTY(EditAnywhere, Category = "Character Properties", meta = (AllowPrivateAccess))
	USceneComponent* holdComponent;

	// Grabs object and attach it to holdComponent.
	void GrabObject();

	// Updates the location of object from tick.
	void UpdateHoldedObjectLocation();

	// Releases objecto from holdComponent.
	void ReleaseObject();

	// Holds reference to the object holded by character.
	AActor* objectHolded;
	// Holds value if an object can be placed on a boxComponent.
	bool canPlaceObject;
	// Holds the location of the boxComponent to place the holded object.
	UPrimitiveComponent* HitComponent;

};
