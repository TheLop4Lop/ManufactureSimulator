// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProductWidget.h"
#include "ComputerProductWidget.generated.h"

DECLARE_DELEGATE_TwoParams(FConfirmOrderEvent, FString, int);

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UComputerProductWidget : public UBaseProductWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	// Delegate event for confirm to spawn RawProduct.
	FConfirmOrderEvent confirmEvent;

	// Quantity of Raw Product orders.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int productQuantity = 1;

	// Sets the order being delivered.
	void SetOrderBeingDelivered(FString order);

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

	// Increment order button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* increaseButton;

	// Decrement order button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* decreaseButton;

	// Confirm product order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* confirmButton;

	// Set implementation for increment and decrement buttons.
	void SetOperationButtons();

	// Set increase button logic for number of orders.
	UFUNCTION()
	void SetIncreaseLogic();

	// Set decrease button logic for number of orders.
	UFUNCTION()
	void SetDecreaseLogic();

	// Set Confirm button logic for orders.
	UFUNCTION()
	void SetConfirmLogic();

	///////////////////////////////////// STORE RAW PRODUCT ORDERS PROPERTIES ////////////////////////////////
	// Sections to store the orders by the player to show on widget.

	// Holds the code order being delivered.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString orderBeingDelivered;

};
