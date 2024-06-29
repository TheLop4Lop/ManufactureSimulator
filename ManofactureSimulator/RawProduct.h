// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProduct.h"
#include "BaseStorage.h"
#include "RawProduct.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API ARawProduct : public ABaseProduct
{
	GENERATED_BODY()

public:
	// Sets product code based on initial BaseStorage struct.
	void SetProductCode(FInitialPieceAttribute productCode);
	// Gets the Product code, this will be readed by the respective machines.
	FInitialPieceAttribute GetRawProductCode();

protected:
	///////////////////////////////////// RAW PRODUCT SETTINGS ////////////////////////////////
	// Section for Raw product properties.

	// Struct for piece identification and properties settings.
	FInitialPieceAttribute rawProductCode;
	
};
