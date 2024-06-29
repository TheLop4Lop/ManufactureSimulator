// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProduct.h"
#include "MachineMolder.h" // Tho access the FProductForm struct.
#include "MolderedProduct.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API AMolderedProduct : public ABaseProduct
{
	GENERATED_BODY()

public:
	// Sets cutted piece product code.
	void SetMolderedProductCode(FProductForm code);
	// Gets cutted piece product code.
	FProductForm GetMolderedProductCode();

protected:
	///////////////////////////////////// PRODUCT PROPERTIES ////////////////////////////////
	// Section for all the product properties.

	// Stores product code to be readed by the next machine in the process.
	FProductForm molderedProductCode;
	
};
