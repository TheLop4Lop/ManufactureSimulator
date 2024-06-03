// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMachinery.h"
#include "PainterMachine.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API APainterMachine : public ABaseMachinery
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	void SetPaint(int Code);

	virtual void AddWidgetFromComputer(class ACharacterController* CharacterController) override;
	virtual void NullWidgetTest() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Painter", meta = (AllowPrivateAccess))
	TArray<UMaterial*> PaintMaterials;
	UMaterial* SelectedPaint;

	UStaticMesh* PieceMesh;

	float TimePainting;

	class UComputerPainterWidget* PainterWidget;

	virtual void ManageEntrancePiece() override;
	virtual void ProducedPiecesExitManager() override;
	
	FString PainterCode;

};
