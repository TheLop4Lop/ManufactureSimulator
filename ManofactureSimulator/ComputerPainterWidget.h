// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComputerMolderWidget.h"
#include "ComputerPainterWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UComputerPainterWidget : public UComputerMolderWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
///////////////////////////////////// FORM PRODUCT BUTTON PROPERTIES ////////////////////////////////
// Section for Form product characteristic buttons.
	
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
	void SetFormsButtonsEvent();

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

	///////////////////////////////////// COMPUTER BUTTON PROPERTIES ////////////////////////////////
	// Section for computer product characteristic orders.

	// Sets confirmButton logic. Triggers an event for machine to recieve production order.
	virtual void SetConfirmButtonLogic() override;
	
};
