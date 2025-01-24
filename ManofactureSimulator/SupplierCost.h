// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MANOFACTURESIMULATOR_API SupplierCost
{
public:
	SupplierCost();
	~SupplierCost();

	// Returns simple cost of Material Quality.
	static float CalculateMaterialQualityCost(FString materialCode, int quantity);

	// Returns simple cost of Material Size.
	static float CalculateMaterialSizeCost(FString sizeCode, int quantity);

	// Returns simple cost of Material Length.
	static float CalculateMaterialLengthCost(FString lengthCode, int quantity);

	// Returns the total value of the order code.
	static float CalculateTotalOrderCost(FString orderCode, int quantity);

private:
	// Gets Discount per quantity.
	static float CalculateDiscount(int quantity);

};
