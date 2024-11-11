// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "ComputerQualityWidget.generated.h"

DECLARE_DELEGATE(FPowerEvent);
DECLARE_DELEGATE(FScanEvent);

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UComputerQualityWidget : public UBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	// Delegate event to power Quality Machine.
	FPowerEvent powerAction;

	// Delegate event to scan product.
	FScanEvent scanAction;

	// Sets status for MachinePower.
	void SetMachinePowerStatus(bool bPowerStatus);

	// Sets Product Material.
	void SetProductMaterial(FString materialCode);

	// Sets Product Size.
	void SetProductSize(FString sizeCode);

	// Sets Product Form.
	void SetProductForm(FString formCode);

	// Sets Product Color.
	void SetProductColor(FString colorCode);

	// Sets Product Last Proccess.
	void SetProductLastProccess(FString proccessCode);

	// Sets ActualQuality progress bar.
	void SetProductActualQuality(float actualQuality);

	// Sets ExpectedQuality progress bar.
	void SetProducExpectedQuality(float expectedQuality);

protected:
	///////////////////////////////////// COMPUTER QUALITY PROPERTIES ////////////////////////////////
	// Section for Computer Quality buttons.

	// Power machine button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* bPower;

	// Scan machine button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* scanButton;

	// Sets implementation of machine buttons.
	void SetQualityButtons();

	// Sets logic for Power button.
	UFUNCTION()
	void SetPowerLogic();

	// Sets logic for Scan button.
	UFUNCTION()
	void SetScanLogic();

	// Holds the value of MachineQuality Power status.
	UPROPERTY(BlueprintReadWrite, Category = "Product Code", meta = (AllowPrivateAccess))
	bool bMachineOn;

	// Material Quality to be assing and read on Widget.
	UPROPERTY(BlueprintReadWrite, Category = "Product Code", meta = (AllowPrivateAccess))
	FString materialQuality;

	// Material Size to be assing and read on Widget.
	UPROPERTY(BlueprintReadWrite, Category = "Product Code", meta = (AllowPrivateAccess))
	FString materialSize;

	// Material Form to be assing and read on Widget.
	UPROPERTY(BlueprintReadWrite, Category = "Product Code", meta = (AllowPrivateAccess))
	FString materialForm;

	// Material Color to be assing and read on Widget.
	UPROPERTY(BlueprintReadWrite, Category = "Product Code", meta = (AllowPrivateAccess))
	FString materialColor;

	// Material Last Proccess to be assing and read on Widget.
	UPROPERTY(BlueprintReadWrite, Category = "Product Code", meta = (AllowPrivateAccess))
	FString materialLastProccess;

	// Actual Quality product progress bar.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* actualQualityBar;

	// Expected Quality product progress bar.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* expectedQualityBar;

	// Custom event to be implemented on Widget; Animation for scann.
    UFUNCTION(BlueprintImplementableEvent, Category = "CustomEvent")
    void OnScannerEvent();

	// Material quality to be assing and read on Widget.
	UPROPERTY(BlueprintReadWrite, Category = "Product Code", meta = (AllowPrivateAccess))
	float productActualQuality;

	// Material quality to be assing and read on Widget.
	UPROPERTY(BlueprintReadWrite, Category = "Product Code", meta = (AllowPrivateAccess))
	float productExpectedQuality;

};
