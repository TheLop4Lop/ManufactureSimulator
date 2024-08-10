// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMachine.h"
#include "MachineMolder.generated.h"

USTRUCT(BlueprintType)
struct FProductForm
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProductMaterial Quality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProductSize Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProductForm Form;

	FProductForm()
        : Quality(EProductMaterial::M1),
          Size(EProductSize::S1),
          Form(EProductForm::F1)
    {}

};

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API AMachineMolder : public ABaseMachine
{
	GENERATED_BODY()

public:
	// Sets the posititon for the Machine Service Door.
	virtual void SetPositionOfServiceDoor() override;

protected:
//////////////////////////////////// PRODUCT PROCESS ////////////////////////////////
	// Section for all the logic in process the product.

	// Checks the actors on the boxEntrance, this will change depending on the machine.
	virtual void CheckEntranceForProduct() override;

	// Gets the cuttedProduct properties and proces production product code.
	void ManageCuttedProductProperties(FString properties);

	///////////////////////////////////// SPAWN PRODUCT ////////////////////////////////
	// Section for spawn product and set properties.

	// Struct for Moldered Product code.
	FProductForm molderedProductCode;

	// Spawn product based on a specific ABaseProduct child, dependes on the process and machine.
	virtual void SpawnProducedProduct() override;
	
};
