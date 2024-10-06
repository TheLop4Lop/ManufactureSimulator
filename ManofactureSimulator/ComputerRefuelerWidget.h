// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "ComputerRefuelerWidget.generated.h"

DECLARE_DELEGATE(FPowerEvent);
DECLARE_DELEGATE(FSecurityDoorEvent);
DECLARE_DELEGATE(FStartOilRefuel);
DECLARE_DELEGATE(FStartLubricantRefuel);

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UComputerRefuelerWidget : public UBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	// Delegate event for power Refueler Machine.
	FPowerEvent powerAction;

	// Delegate event for Segurity door.
	FSecurityDoorEvent doorAction;

	// Delegate event to fill oil canister event.
	FStartOilRefuel oilRefuelAction;

	// Delegate event to fill lubricant canister event.
	FStartLubricantRefuel lubricantRefuelAction;

protected:
///////////////////////////////////// COMPUTER REFUELER PROPERTIES ////////////////////////////////
// Section for Computer Refueler buttons.

	// Power machine button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* bPower;

	// Open/Close ServiceDoor button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* securityDoor;

	// Start filling Oil Canister button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* fillOilCanister;

	// Start filling Lubricant Canister button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* fillLubricantCanister;

	// Called in Native construct, method calls all other Button Logic Implementations.
	void SetButtonsLogicEvents();

	// Sets Power button logic implementation.
	UFUNCTION()
	void SetPowerButtonLogic();

	// Sets SecurityDoor button logic implementation.
	UFUNCTION()
	void SetSecurityDoorButtonLogic();

	// Sets OilCanister button logic implementation.
	UFUNCTION()
	void SetOilCanisterButtonLogic();

	// Sets lubricantCanister button logic implementation.
	UFUNCTION()
	void SetlubricantCanisterButtonLogic();

};
