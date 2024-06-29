// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "BaseProductWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UBaseProductWidget : public UBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	///////////////////////////////////// MATERIAL PRODUCT BUTTON PROPERTIES ////////////////////////////////
	// Section for Material product characteristic buttons.

	// Material M1 button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* M1;

	// Material M2 button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* M2;

	// Material M3 button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* M3;

	// Set implementation for Material buttons.
	void SetMaterialsButtonsEvent();

	// Set M1 button logic.
	UFUNCTION()
	void SetM1ButtonLogic();

	// Set M2 button logic.
	UFUNCTION()
	void SetM2ButtonLogic();

	// Set M3 button logic.
	UFUNCTION()
	void SetM3ButtonLogic();

	// Material string for implement product code.
	FString materialType;

	///////////////////////////////////// SIZE PRODUCT BUTTON PROPERTIES ////////////////////////////////
	// Section for Size product characteristic buttons.

	// Size S1 button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* S1;

	// Size S2 button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* S2;

	// Size S3 button.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* S3;

	// Set implementation for Size buttons.
	void SetSizeButtonsEvent();

	// Set S1 button logic.
	UFUNCTION()
	void SetS1ButtonLogic();

	// Set S2 button logic.
	UFUNCTION()
	void SetS2ButtonLogic();

	// Set S3 button logic.
	UFUNCTION()
	void SetS3ButtonLogic();

	// Size string for implement product code.
	FString sizeType;
	
};
