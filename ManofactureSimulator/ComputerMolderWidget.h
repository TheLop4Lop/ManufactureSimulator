// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ComputerMolderWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UComputerMolderWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	virtual void SetBaseMachineComputer(class ABaseMachinery* NewComputer);
	void SetWrongOrderName(FString Order);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StageProduction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WrongOrderName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UImage* PowerLed;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UImage* FigureConfiguration;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UProgressBar* MaintenanceBar;

	void SetMaintenanceBarProgress(float percent);

protected:
	class ABaseCharacter* Character;
	class AMoldingMachine* MoldingMachine;

	//Machine Power and Maintenance
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Power;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Maintenace;

	void SetPowerAndMaintenance();

	UFUNCTION()
	void PowerButtonClick();

	UFUNCTION()
	void MaintenaceButtonClick();

	//Stage Production Buttons
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* M1S1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* M1S2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* M1S3;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* M2S1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* M2S2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* M2S3;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* M3S1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* M3S2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* M3S3;

	void SetProductionPieceButtons();

	UFUNCTION()
	void M1S1ButtonClick();

	UFUNCTION()
	void M1S2ButtonClick();

	UFUNCTION()
	void M1S3ButtonClick();

	UFUNCTION()
	void M2S1ButtonClick();

	UFUNCTION()
	void M2S2ButtonClick();

	UFUNCTION()
	void M2S3ButtonClick();

	UFUNCTION()
	void M3S1ButtonClick();

	UFUNCTION()
	void M3S2ButtonClick();

	UFUNCTION()
	void M3S3ButtonClick();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ExitButton;

	void SetExitButton();

	UFUNCTION()
	virtual void ExitButtonClick();
	
	bool TogglePower;
	FLinearColor LedColor;

	void ChangePowerLedColor();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Figure1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Figure2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Figure3;

	void SetFigureButtons();

	UFUNCTION()
	virtual void Figure1ButtonClick();

	UFUNCTION()
	virtual void Figure2ButtonClick();

	UFUNCTION()
	virtual void Figure3ButtonClick();

	FLinearColor FigureColor;
	
};
