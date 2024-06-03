// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMachinery.h"
#include "CutterMachine.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API ACutterMachine : public ABaseMachinery
{
	GENERATED_BODY()

private:
	virtual void RawPieceEntranceManager() override;
	virtual void GetEntrancePiece() override;
	virtual void ManageEntrancePiece() override;

	class AInitialPiece* initialPiece;

};
