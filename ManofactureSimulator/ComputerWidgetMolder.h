// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMachineComputerWidget.h"
#include "ComputerWidgetMolder.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UComputerWidgetMolder : public UBaseMachineComputerWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

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

	virtual void ExecuteConfirmButton() override;
	
};
