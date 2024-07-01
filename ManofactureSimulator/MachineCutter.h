// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMachine.h"
#include "BaseStorage.h"
#include "MachineCutter.generated.h"

USTRUCT(BlueprintType)
struct FBasicProduct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProductMaterial Quality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProductSize Size;

	FBasicProduct() 
		: Quality(EProductMaterial::M1),
		  Size(EProductSize::S1)
	{}

};

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API AMachineCutter : public ABaseMachine
{
	GENERATED_BODY()

protected:
	///////////////////////////////////// PRODUCT PROCESS ////////////////////////////////
	// Section for all the logic in process the product.

	// Checks the actors on the boxEntrance, this will change depending on the machine.
	virtual void CheckEntranceForProduct() override;

	// Gets the initialPieceAtributes and convert it to BaseMachine product code.
	void ManageInitialProductProperties(FString properties);

	///////////////////////////////////// SPAWN PRODUCT ////////////////////////////////
	// Section for spawn product and set properties.
	
	// Struct for Cutted Product code.
	FBasicProduct cuttedProductCode;

	// Spawn product based on a specific ABaseProduct child, dependes on the process and machine.
	virtual void SpawnProducedProduct() override;

};
