// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProductWidget.h"
#include "BaseMachineComputerWidget.generated.h"

DECLARE_DELEGATE(FProductDoor);
DECLARE_DELEGATE(FServideDoor);
DECLARE_DELEGATE_OneParam(FProcessOrder, FString);

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UBaseMachineComputerWidget : public UBaseProductWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	// Delegate event for confirm production order for machine.
	FProcessOrder confirmProductionCode;

	// Delegate event for product door to open or close.
	FProductDoor productDoorAction;

	// Delehate event for service machine door to open or close.
	FServideDoor serviceDoorAction;

protected:
	///////////////////////////////////// COMPUTER BUTTON PROPERTIES ////////////////////////////////
	// Section for computer product characteristic orders.

	// Confirm product order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* confirmButton;

	// Sets implementation for confirmButton.
	void SetConfirmButton();

	// Sets confirmButton logic. Triggers an event for machine to recieve production order.
	UFUNCTION()
	void SetConfirmButtonLogic();

	virtual void ExecuteConfirmButton();

	// Open de product door of the machine for product inspection.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* productDoorButton;

	// Set ProductDoorButton logic. Triggers an event for machine to open product Door.
	UFUNCTION()
	void SetProductDoorLogic();

	// Open de product door of the machine for product inspection.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* serviceDoorButton;

	// Set ProductDoorButton logic. Triggers an event for machine to open product Door.
	UFUNCTION()
	void SetServiceDoorLogic();

	// Set Machine door buttons.
	void SetMachineDoorsButtons();
	
};
