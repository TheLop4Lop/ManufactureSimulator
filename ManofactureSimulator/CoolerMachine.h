// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMachinery.h"
#include "CoolerMachine.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API ACoolerMachine : public ABaseMachinery
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Oven", meta = (AllowPrivateAccess))
	float SpeedFactor = 1.f;

	UStaticMesh* ProductMesh;
	UMaterial* BakedMaterial;

	virtual void ManageEntrancePiece() override;
	virtual void ProducedPiecesExitManager() override;
};
