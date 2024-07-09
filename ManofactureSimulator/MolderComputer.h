// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseComputer.h"
#include "MolderComputer.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API AMolderComputer : public ABaseComputer
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	// Adds widget and assign the player controller to it.
	virtual void AddWidgetFromComputer(class ACharacterController* CharacterController);

protected:
	///////////////////////////////////// MACHINE COMPUTER PROPERTIES ////////////////////////////////
	// Sections for the actor properties.
	
	// Reference to widget Production Widget for manage production machine product.
	class UComputerMolderWidget* computerWidget;

	// Reference to cutter machine in the world.
	class AMachineMolder* cutterMachine;

	void PublicWidgetBindResetController();

	// Gett the product order for pass it on to Storage manager.
	void WidgetBindProductOrder(FString productCode);

	
};