// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComputerProductWidget.h"
#include "ManagerSupplierWidget.generated.h"

DECLARE_DELEGATE_OneParam(FSelectionOrders, TArray<int>);

USTRUCT(BlueprintType)
struct FOrderSelection
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int orderQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString selectionOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float estimatedEarnings;

};

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UManagerSupplierWidget : public UComputerProductWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	// Delegate executed on confimr button to pass index selection to ManagerComputer.
	FSelectionOrders ordersSelectedDelegate;

	// Sets the value of qualityMaterialCost.
	void SetValueofCurrentMoney(float money);

	// Set a series of orders to select from, size fixed on Max orders to select.
	void SetOrdersToSelect(TArray<FOrderSelection> generatedOrders);

	// Set selected Orders from Manager Computer memory.
	void DisplaySelectedOrdersFromMemory(TArray<FString> ordersSelected);

protected:
	///////////////////////////////////// MONEY PROPERTIES ////////////////////////////////
	// Section for buying material.

	// Holds the value of the actual money to spend.
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	float currentMoney;

	// Holds value of Quality Material cost.
	float qualityMaterialCost;

	// Holds value of the Size Material cost.
	float sizeMaterialCost;

	// Holds value of the Length Material cost.
	float lengthMaterialCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	float totalMaterialCost;

	// Gets from blueprint the material code value;
	UFUNCTION(BlueprintCallable, Category = "Convert String To Money")
	void SetMaterialCost(FString qualityCode);

	// Holds the value of the qualityCostCode to  update order price;
	FString qualityCostCode;

	// Gets from blueprint the size code value;
	UFUNCTION(BlueprintCallable, Category = "Convert String To Money")
	void SetSizeCost(FString sizeCode);

	// Holds the value of the qualityCostCode to  update order price;
	FString sizeCostCode;

	// Gets from blueprint the length code value;
	UFUNCTION(BlueprintCallable, Category = "Convert String To Money")
	void SetLengthCost(FString lengthCode);

	// Holds the value of the qualityCostCode to  update order price;
	FString lengthCostCode;

	// Updates Value of totalMaterialCost.
	UFUNCTION(BlueprintCallable, Category = "Convert String To Money")
	void UpdateTotalMaterialCostValue(int orderQuantity);

	///////////////////////////////////// ORDER SELECTION PROPERTIES ////////////////////////////////
	// Section for order selection proccess.

	// Buttons for Order selection.

	// Option for Order 1 Button.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonOrder;

	// Option for Order 2 Button.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonOrder_1;

	// Option for Order 3 Button.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonOrder_2;

	// Option for Order 4 Button.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonOrder_3;

	// Option for Order 5 Button.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonOrder_4;

	// Option for Order 6 Button.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonOrder_5;

	// Option for Order 7 Button.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonOrder_6;

	// Option for Order 8 Button.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonOrder_7;

	// Option for Order 9 Button.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonOrder_8;

	// Option for Order 10 Button.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonOrder_9;

	// Text for button orders representation.

	// Option for Order 1 text.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* textButton;

	// Option for Order 2 text.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* textButton_1;

	// Option for Order 3 text.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* textButton_2;

	// Option for Order 4 text.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* textButton_3;

	// Option for Order 5 text.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* textButton_4;

	// Option for Order 6 text.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* textButton_5;

	// Option for Order 7 text.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* textButton_6;

	// Option for Order 8 text.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* textButton_7;

	// Option for Order 9 text.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* textButton_8;

	// Option for Order 10 text.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* textButton_9;

	// Holds the order codes for the orders to select by the player.
	TArray<FOrderSelection> orderToSelect;

	// Holds the code value to be implemente into a method on blueprint to display code.
	UPROPERTY(BlueprintReadWrite, Category = "Code Selection", meta = (AllowPrivateAccess))
	FString selectedButtonCode;

	// Sets buttons implementation.
	void ImplementButtons();

	// Sets the logic for ButtonOrder.
	UFUNCTION()
	void SetButtonOrderLogic();

	// Sets the logic for ButtonOrder 1.
	UFUNCTION()
	void SetButtonOrderLogic_1();

	// Sets the logic for ButtonOrder 2.
	UFUNCTION()
	void SetButtonOrderLogic_2();

	// Sets the logic for ButtonOrder 3.
	UFUNCTION()
	void SetButtonOrderLogic_3();

	// Sets the logic for ButtonOrder 4.
	UFUNCTION()
	void SetButtonOrderLogic_4();

	// Sets the logic for ButtonOrder 5.
	UFUNCTION()
	void SetButtonOrderLogic_5();

	// Sets the logic for ButtonOrder 6.
	UFUNCTION()
	void SetButtonOrderLogic_6();

	// Sets the logic for ButtonOrder 7.
	UFUNCTION()
	void SetButtonOrderLogic_7();

	// Sets the logic for ButtonOrder 8.
	UFUNCTION()
	void SetButtonOrderLogic_8();

	// Sets the logic for ButtonOrder 9.
	UFUNCTION()
	void SetButtonOrderLogic_9();

	// Displays the Selection Code Options on button text block.
	void DisplayButtonCodeOptions();

	///////////////////////////////////// RESET SELECTION ORDERS COST PROPERTIES ////////////////////////////////
	// Section for reset orders options and cost.

	// Reset Orders for selection button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* resetOrdersButton;

	// Holds the value of reset cost.
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	float resetCost;

	// Holds the value of the penalty due quantity of reset and customers penalty.
	float penaltyPerReset;

	// Holds the quantity of resets.
	int penaltyPerResetCnt;

	///////////////////////////////////// ORDER SELECTED PROPERTIES ////////////////////////////////
	// Section for orders selected to produce.

	// Selected order text 1.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SO_Text1;

	// Selected order text 2.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SO_Text2;

	// Selected order text 3.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SO_Text3;

	// Selected order text 4.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SO_Text4;

	// Selected order text 5.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SO_Text5;

	// Selected order text 6.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SO_Text6;

	///////////////////////////////////// SELECTED ORDERS PROPERTIES ////////////////////////////////
	// Section for reset orders options and cost.

	// Implements Accept button logic interction.
	void ImplementAcceptButton();

	// Set logic for Accept button.
	UFUNCTION()
	void SetAcceptButtonLogic();

	// Image to represent a light indicator for missing selection.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* selectionLight;

	// Accept the orders for the day.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* acceptSelectedOrders;

	// Holds the value of total estimated earnings.
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	float estimatedEarnings;

	// Holds the value of the selected index to 
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<int> idexSelected;

	// Bool responsable to hold the status of orders of the day selected, once active cannot change status.
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool orderOfTheDaySelected;

	// Method to chnge visibility, implemented on blueprint.
	UFUNCTION(BlueprintImplementableEvent)
	void ChangeSelectedOrdersVisibility();

};
