// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachinePainter.h"
#include "MachineOven.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API AMachineOven : public AMachinePainter
{
	GENERATED_BODY()

protected:
	//////////////////////////////////// PRODUCT PROCESS ////////////////////////////////
	// Section for all the logic in process the product.

	// Checks the actors on the boxEntrance, this will change depending on the machine.
	virtual void CheckEntranceForProduct() override;

	// Gets the molderedProduct properties and proces production product code.
	void ManageMolderedProductProperties(FString properties);
	
};
