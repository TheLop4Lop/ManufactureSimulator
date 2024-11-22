// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProductWidget.h"
#include "BaseMachineComputerWidget.generated.h"

DECLARE_DELEGATE(FPowerMachine);
DECLARE_DELEGATE(FServiceMachine);

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
	// Delegate evento to change Power status on machine.
	FPowerMachine powerAction;

	// Delegate event to set Machine on Service status.
	FServiceMachine serviceAction;

	// Delegate event for confirm production order for machine.
	FProcessOrder confirmProductionCode;

	// Delegate event for product door to open or close.
	FProductDoor productDoorAction;

	// Delehate event for service machine door to open or close.
	FServideDoor serviceDoorAction;

	// Sets the color of the Power Button Light.
	void SetPowerLight(bool bMachinePower);

	// Set Oil Bar percent level.
	void SetOilLevel(float oilLevel);

	// Set Lubricant Bar percent level.
	void SetLubricantLevel(float lubricantLevel);

protected:
	///////////////////////////////////// COMPUTER BUTTON PROPERTIES ////////////////////////////////
	// Section for computer product characteristic orders.

	// Machine Power Button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* powerButton;

	// Machine Power Button Light indicator.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* powerLight;

	// Machine service button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* serviceButton;

	// Sets implementation for machine power and service.
	void SetMachineBaseButtons();

	// Implements logic event for Power Button.
	UFUNCTION()
	void SetPowerButtonLogic();

	// Implements logic event for Service Button.
	UFUNCTION()
	void SetServiceButtonLogic();

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

	// Oil Machine Level progress Bar.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* oilLevelBar;

	// Lubricant Machine Level progress Bar.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* lubricantLevelBar;
	
};
