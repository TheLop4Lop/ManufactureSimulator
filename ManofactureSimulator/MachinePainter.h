// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMachine.h"
#include "MachinePainter.generated.h"

USTRUCT(BlueprintType)
struct FProductColor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPieceMaterial Quality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPieceSize Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPieceForm Form;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPieceColor Color;

	FProductColor()
		: Quality(EPieceMaterial::QUALITY_LOW),
          Size(EPieceSize::SIZE_SMALL),
          Form(EPieceForm::FORM_CONE),
		  Color(EPieceColor::COLOR_BLUE)
	{}

};

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API AMachinePainter : public ABaseMachine
{
	GENERATED_BODY()

protected:
	//////////////////////////////////// PRODUCT PROCESS ////////////////////////////////
	// Section for all the logic in process the product.

	// Checks the actors on the boxEntrance, this will change depending on the machine.
	virtual void CheckEntranceForProduct() override;

	// Gets the molderedProduct properties and proces production product code.
	void ManageMolderedProductProperties(FString properties);

	///////////////////////////////////// SPAWN PRODUCT ////////////////////////////////
	// Section for spawn product and set properties.

	// Holds the color 1 for the paint process.
	UPROPERTY(EditAnywhere, Category = "Color Spawn Product", meta = (AllowPrivateProperty))
	TArray<UMaterial*> color1Quality;

	// Holds the color 2 for the paint process.
	UPROPERTY(EditAnywhere, Category = "Color Spawn Product", meta = (AllowPrivateProperty))
	TArray<UMaterial*> color2Quality;

	// Holds the color 3 for the paint process.
	UPROPERTY(EditAnywhere, Category = "Color Spawn Product", meta = (AllowPrivateProperty))
	TArray<UMaterial*> color3Quality;

	// Struct for Moldered Product code.
	FProductColor paintedProductCode;

	// Spawn product based on a specific ABaseProduct child, dependes on the process and machine.
	virtual void SpawnProducedProduct() override;
	
};
