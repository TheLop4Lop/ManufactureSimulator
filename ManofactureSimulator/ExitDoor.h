// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseComputer.h"
#include "ExitDoor.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API AExitDoor : public ABaseComputer
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Adds widget and assign the player controller to it.
	virtual void AddWidgetFromComputer(class ACharacterController* CharacterController) override;

protected:

	///////////////////////////////////// EXIT DOOR PROPERTIES ////////////////////////////////
	// Sections for the actor properties.
	
	// Reference to widget Production Widget to review player's info.
	class UExitDoorWidget* exitDoorWidget;

	// Called when the data is obtain for display.
	void GetExitDoorInfo(struct FExitSimulationInfo exitInfo);

	// Holds reference to Manager COmputer in world.
	class AManagerComputer* managerComputer;

};
