// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProduct.h"
#include "CuttedProduct.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API ACuttedProduct : public ABaseProduct
{
	GENERATED_BODY()

public:
	// Sets cutted piece product code.
	void SetCuttedProductCode(FString& code);
	// Gets cutted piece product code.
	FString& GetCuttedProductCode();

protected:
	///////////////////////////////////// PRODUCT PROPERTIES ////////////////////////////////
	// Section for all the product properties.

	// Stores product code to be readed by the next machine in the process.
	FString cuttedProductCode;
	
};
