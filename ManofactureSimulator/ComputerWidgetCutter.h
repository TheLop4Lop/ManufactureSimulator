// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMachineComputerWidget.h"
#include "ComputerWidgetCutter.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UComputerWidgetCutter : public UBaseMachineComputerWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

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
	
	virtual void ExecuteConfirmButton() override;
};
