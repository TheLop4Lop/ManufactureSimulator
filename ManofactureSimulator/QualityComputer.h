// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseComputer.h"
#include <map>
#include <string>
#include "QualityComputer.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API AQualityComputer : public ABaseComputer
{
	GENERATED_BODY()

public:
	AQualityComputer();

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Adds widget and assign the player controller to it.
	virtual void AddWidgetFromComputer(class ACharacterController* CharacterController);

protected:
	///////////////////////////////////// BASE COMPUTER PROPERTIES ////////////////////////////////
	// Sections for the actor properties.

	// Resets the character controller to move the character around.
	virtual void WidgetBindResetController() override;

	///////////////////////////////////// MACHINE COMPUTER PROPERTIES ////////////////////////////////
	// Sections for the actor properties.
	
	// Reference to widget Production Widget for manage production machine product.
	class UComputerQualityWidget* computerWidget;

	// Reference to Refueler machine in the world.
	class AMachineQuality* qualityMachine;

	// Changes Machine Power Status.
	void SetPowerStatus();
	
	// Calls scann product interaction.
	void ScanProductAction();

	// Controls power floww info to widget interaction.
	bool machineQualityPowered;

	// Material Quality to be assing and read on Widget.
	UPROPERTY(EditAnywhere, Category = "Product Code", meta = (AllowPrivateAccess))
	FString materialQuality;

	// Material Size to be assing and read on Widget.
	UPROPERTY(EditAnywhere, Category = "Product Code", meta = (AllowPrivateAccess))
	FString materialSize;

	// Material Form to be assing and read on Widget.
	UPROPERTY(EditAnywhere, Category = "Product Code", meta = (AllowPrivateAccess))
	FString materialForm;

	// Material Color to be assing and read on Widget.
	UPROPERTY(EditAnywhere, Category = "Product Code", meta = (AllowPrivateAccess))
	FString materialColor;

	// Material Last Proccess to be assing and read on Widget.
	UPROPERTY(EditAnywhere, Category = "Product Code", meta = (AllowPrivateAccess))
	FString materialLastProccess;

	// Material quality to be assing and read on Widget.
	UPROPERTY(EditAnywhere, Category = "Product Code", meta = (AllowPrivateAccess))
	float productActualQuality;

	// Material quality to be assing and read on Widget.
	UPROPERTY(EditAnywhere, Category = "Product Code", meta = (AllowPrivateAccess))
	float productExpectedQuality;

	// Read Product Properties.
	void ReadProductProperties(FString productCode);

	// Read Product Quality.
	void ReadProductQuality(float productQuality);

	// Set product materialQuality.
	void GetMaterialCodeSetMaterialQuality(FString materialCode);

	// Set product materialSize.
	void GetSizeCodeSetMaterialSize(FString sizeCode);

	// Set product materialForm.
	void GetFormCodeSetMaterialForm(FString formCode);

	// Set product materialColor.
	void GetColorCodeSetMaterialColor(FString colorCode);
	
};
