// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProductWidget.h"
#include "ComputerCutterWidget.generated.h"

DECLARE_DELEGATE_OneParam(FProcessOrder, FString);

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UComputerCutterWidget : public UBaseProductWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	// Delegate event for confirm production order for machine.
	FProcessOrder confirmProductionCode;

protected:
///////////////////////////////////// LENGTH PRODUCT BUTTON PROPERTIES ////////////////////////////////
	// Section for Length product characteristic buttons.
	
	// Length L1 button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* L1;

	// Length L2 button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* L2;

	// Length L3 button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* L3;

	// Set implementation for Length buttons.
	void SetLengthsButtonsEvent();

	// Set L1 button logic.
	UFUNCTION()
	void SetL1ButtonLogic();

	// Set L2 button logic.
	UFUNCTION()
	void SetL2ButtonLogic();

	// Set L3 button logic.
	UFUNCTION()
	void SetL3ButtonLogic();

	// Length string for implement product code.
	FString lengthType;

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
	
};