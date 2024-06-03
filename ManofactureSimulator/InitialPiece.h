// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "InitialPiece.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API AInitialPiece : public APiece
{
	GENERATED_BODY()

public:
	void SetQuantityProduction(int& Quantity);
	int GetQuantityProduction();

private:
	UPROPERTY(EditAnywhere, Category = "Production", meta = (AllowPrivateAccess))
	int InitialQuantity;
	
};
