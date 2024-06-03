// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMachinery.h"
#include "OvenMachine.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API AOvenMachine : public ABaseMachinery
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Oven", meta = (AllowPrivateAccess))
	TArray<UMaterial*> FreshMaterial;

	UPROPERTY(EditAnywhere, Category = "Oven", meta = (AllowPrivateAccess))
	TArray<UMaterial*> BakedMaterial;
	UMaterial* BakedColor;
	float BakeTime;

	UStaticMesh* ProductMesh;

	void SetBakedColor(UMaterial* Color);

	virtual void ManageEntrancePiece() override;
	virtual void ProducedPiecesExitManager() override;

	FString ProcessCode;
	
};
