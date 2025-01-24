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

	// Sets the total amount of earnigns needed for the day.
	void SetGoal(int goal);

	// Sets the current amount of earnings.
	void SetCurrent(int current);

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

	// Holds the total earnign of the day.
	UPROPERTY(BlueprintReadWrite, Category = "Earning Data", meta = (AllowPrivateAccess))
	int earningGoal;

	// Holds the current earnings.
	UPROPERTY(BlueprintReadWrite, Category = "Earning Data", meta = (AllowPrivateAccess))
	int currentEarning;
	
};
