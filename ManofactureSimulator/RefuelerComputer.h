// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseComputer.h"
#include "RefuelerComputer.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API ARefuelerComputer : public ABaseComputer
{
	GENERATED_BODY()

public:
	ARefuelerComputer();

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Adds widget and assign the player controller to it.
	virtual void AddWidgetFromComputer(class ACharacterController* CharacterController);

protected:
	///////////////////////////////////// BASE COMPUTER PROPERTIES ////////////////////////////////
	// Sections for the actor properties.

	// Resets the character controller to move the character around.
	virtual void WidgetBindResetController() override;

	///////////////////////////////////// MACHINE COMPUTER PROPERTIES ////////////////////////////////
	// Sections for the actor properties.
	
	// Reference to widget Production Widget for manage production machine product.
	class UComputerRefuelerWidget* computerWidget;

	// Reference to Refueler machine in the world.
	class ARefueler* refuelerMachine;
	
	// Calls machine security door for interaction.
	void CallsSecurityDoorAction();

	// Calls interaction for oil supply
	void CallsOilRefuel();

	// Calls interaction for lubricant supply
	void CallsLubricantRefuel();
	
};
