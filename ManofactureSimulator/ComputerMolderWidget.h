// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProductWidget.h"
#include "ComputerMolderWidget.generated.h"

DECLARE_DELEGATE_OneParam(FProcessOrder, FString);

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UComputerMolderWidget : public UBaseProductWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	// Delegate event for confirm production order for machine.
	FProcessOrder confirmProductionCode;

protected:
///////////////////////////////////// FORM PRODUCT BUTTON PROPERTIES ////////////////////////////////
// Section for Form product characteristic buttons.
	
	// Form F1 button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* F1;

	// Form F2 button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* F2;

	// Form F3 button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* F3;

	// Set implementation for Form buttons.
	void SetFormsButtonsEvent();

	// Set F1 button logic.
	UFUNCTION()
	void SetF1ButtonLogic();

	// Set F2 button logic.
	UFUNCTION()
	void SetF2ButtonLogic();

	// Set F3 button logic.
	UFUNCTION()
	void SetF3ButtonLogic();

	// Form string for implement product code.
	FString formType;

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
