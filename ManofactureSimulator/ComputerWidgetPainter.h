// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComputerWidgetMolder.h"
#include "ComputerWidgetPainter.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UComputerWidgetPainter : public UComputerWidgetMolder
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

///////////////////////////////////// COLOR PRODUCT BUTTON PROPERTIES ////////////////////////////////
// Section for Color product characteristic buttons.
	
	// Form C1 button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* C1;

	// Form C2 button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* C2;

	// Form C3 button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* C3;

	// Set implementation for Form buttons.
	void SetColorsButtonsEvent();

	// Set C1 button logic.
	UFUNCTION()
	void SetC1ButtonLogic();

	// Set C2 button logic.
	UFUNCTION()
	void SetC2ButtonLogic();

	// Set C3 button logic.
	UFUNCTION()
	void SetC3ButtonLogic();

	// Form string for implement product code.
	FString colorType;

	virtual void ExecuteConfirmButton() override;
	
};
