// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProductionScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UProductionScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Sets Cutter Machine color Status.
	void SetCutterMachineColorStatus(FColor machineStatus);

	// Sets Molder Machine color Status.
	void SetMolderMachineColorStatus(FColor machineStatus);

	// Sets Painter Machine color Status.
	void SetPainterMachineColorStatus(FColor machineStatus);

	// Sets Oven Machine color Status.
	void SetOvenMachineColorStatus(FColor machineStatus);

	void SetPiecesProduced(int data);

private:
	///////////////////////////////////// PRODUCTION SCREEN MACHINES ////////////////////////////////
	// Production Screen actor images.

	// Holds reference for Cutter Machine to change color status.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* cutterImage;

	// Holds reference for Molder Machine to change color status.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* molderImage;

	// Holds reference for Painter Machine to change color status.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* painterImage;

	// Holds reference for Oven Machine to change color status.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* ovenImage;

	UPROPERTY(BlueprintReadWrite, Category = "Test Data", meta = (AllowPrivateAccess))
	int producedPieces;
	
};
