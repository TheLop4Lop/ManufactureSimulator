// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseComputer.h"
#include "PainterComputer.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API APainterComputer : public ABaseComputer
{
	GENERATED_BODY()

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
	class UComputerWidgetPainter* computerWidget;

	// Reference to cutter machine in the world.
	class AMachinePainter* painterMachine;

	// Calls machine method to change Power Status.
	void CallPowerAction();

	// Calls machine method to enter service mode.
	void CallServiceAction();

	void PublicWidgetBindResetController();

	// Gett the product order for pass it on to Storage manager.
	void WidgetBindProductOrder(FString productCode);

	// Calls machine for product door interaction.
	void CallProductDoorAction();
	
	// Calls machine service door for interaction.
	void CallsServiceDoorAction();

	// Recieve the wrongCode on entrance by Machine.
	virtual void GetTheWrongCodeOnEntrance(FString codeOnEntrance) override;
	
};
