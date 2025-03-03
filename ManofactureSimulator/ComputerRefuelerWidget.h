// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "ComputerRefuelerWidget.generated.h"

DECLARE_DELEGATE(FPowerEvent);
DECLARE_DELEGATE(FSecurityDoorEvent);
DECLARE_DELEGATE(FStartOilRefuel);
DECLARE_DELEGATE(FStartLubricantRefuel);

DECLARE_DELEGATE(FBuyOil);
DECLARE_DELEGATE(FBuyLubricant);

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

	// Delegate event to buy oil from supplier.
	FBuyOil buyOil;

	// Delegate event to buy lubricant from supplier.
	FBuyLubricant buyLubricant;

	// Sets the color of the Power Button Light.
	void SetPowerLight(bool bMachinePower);

	// Sets value of Oil Bar.
	void SetOilBarLevel(float oilevel);

	// Sets value of Lubricant Bar.
	void SetLubricantBarLevel(float lubricantLevel);

	// Sets the oil cost on Widget.
	void SetOilCost(float oilResetCost);

	// Sets the lubricant cost on Widget.
	void SetLubricantCost(float lubricantResetCost);

protected:
	///////////////////////////////////// COMPUTER REFUELER PROPERTIES ////////////////////////////////
	// Section for Computer Refueler buttons.

	// Power machine button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* bPower;

	// Machine Power Button Light indicator.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* powerLight;

	// Open/Close ServiceDoor button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* securityDoor;

	// Start filling Oil Canister button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* fillOilCanister;

	// Start filling Lubricant Canister button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* fillLubricantCanister;

	// Refueler Oil Deposit Indicator .
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* oilBar;

	// Refueler Lubricant Deposit Indicator .
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* lubricantBar;

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

	///////////////////////////////////// OIL & LUBRICANT SUPPLY PROPERTIES ////////////////////////////////
	// Section for oil and Lubricant supply.

	// Buys oil from supplier.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* buyOilButton;

	// Buys lubricant from supplier.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* buyLubricantButton;

	// Holds the informatin of oil cost.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* oilCost;

	// Holds the informatin of oil cost.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* lubricantCost;

	// Set buy buttons events.
	void SetBuyButtonsEvents();

	// Set Buy oil Button Logic.
	UFUNCTION()
	void SetBuyOilButtonLogic();

	// Set Buy lubricant Button Logic.
	UFUNCTION()
	void SetBuyLubricantButtonLogic();

};
