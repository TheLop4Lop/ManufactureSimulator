// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMachinery.h"
#include "MoldingMachine.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API AMoldingMachine : public ABaseMachinery
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	void SetMoldingMesh(int Code);

	virtual void AddWidgetFromComputer(class ACharacterController* CharacterController) override;
	virtual void NullWidgetTest() override;

private:
	UPROPERTY(EditAnywhere, Category = "Molding Pieces", meta = (AllowPrivateAccess))
	TArray<class UStaticMesh*> MoldingMesh;

	class UComputerMolderWidget* MolderWidget;

	class UStaticMesh* SelectedMesh;
	float TimeMolding;

	FString CutterCode;
	
	virtual void ManageEntrancePiece() override;
	virtual void ProducedPiecesExitManager() override;

	
};
