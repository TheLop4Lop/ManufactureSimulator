// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComputerProductWidget.h"
#include "ManagerSupplierWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UManagerSupplierWidget : public UComputerProductWidget
{
	GENERATED_BODY()

public:
	// Sets the value of qualityMaterialCost.
	void SetValueofCurrentMoney(float money);

protected:
	///////////////////////////////////// MONEY PROPERTIES ////////////////////////////////
	// Holds the values of the current values of the selected code.

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

};
