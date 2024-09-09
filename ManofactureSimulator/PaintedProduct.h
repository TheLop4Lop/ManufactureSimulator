// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProduct.h"
#include "PaintedProduct.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API APaintedProduct : public ABaseProduct
{
	GENERATED_BODY()

public:
	// Changes the status from not ready to store to ready
	void ProductReadyForStorage();
	
};
