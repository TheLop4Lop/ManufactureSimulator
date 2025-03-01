// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "ExitDoorWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UExitDoorWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	// Set production time in seconds
	void SetPlayerTimeInProduction(float productionPlayed);

	// Set the max productes produced in the sesion.
	void SetTotalProductsProduced(int totalProducts);

	// Set the code of the product with more pproduction in storage.
	void SetMostProducedProduct(FString productCode);

	// Set the total amount of earnings.
	void SetTotalEarnings(float totalEarnings);

	// Set the lost money through production, based on player's mistakes.
	void SetLostMoney(float lost);

protected:
	///////////////////////////////////// EXIT DOOR PROPERTIES ////////////////////////////////
	// Sections for the actor properties.

	// Holds the information for time simulated played, in seconds.
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	float playerTimeProduction;
	
	// Holds the information for the max quantity of Products prduced by the player.
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	int playerProductsProduced;
	
	// Holds the information for the code of the most Product produced.
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	FString playerMostProducedProduct;
	
	// Holds the earnings produced.
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	float earnings;
	
	// Holds the information of the wrong pieces produced in money productivity.
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	float lostMoney;
	
};
