// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseComputer.h"
#include <map>
#include <string>
#include "QualityComputer.generated.h"

UENUM(BlueprintType)
enum class EMaterial : uint8 
{
	M1,
	M2,
	M3

};

UENUM(BlueprintType)
enum class ESize : uint8
{
	S1,
	S2,
	S3

};

UENUM(BlueprintType)
enum class EForm : uint8
{
	F1,
	F2,
	F3

};

UENUM(BlueprintType)
enum class EColor : uint8
{
	C1,
	C2,
	C3

};

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

private:
	///////////////////////////////////// MAP CONVERTION ////////////////////////////////
	// Singleton implementation for String-ENUM convertion, this help to all child classes access to transformation.

	// Static MATERIAL map for string to ENUM data, this is used for product interpretation in respective machine.
	static std::map<FString, EMaterial> StringToEnumMaterialMap;

	// Static SIZE map for string to ENUM data, this is used for product interpretation in respective machine.
	static std::map<FString, ESize> StringToEnumSizeMap;

	// Static FORM map for string to ENUM data, this is used for product interpretation in respective machine.
	static std::map<FString, EForm> StringToEnumFormMap;

	// Static COLOR map for string to ENUM data, this is used for product interpretation in respective machine.
	static std::map<FString, EColor> StringToEnumColorMap;

protected:
	///////////////////////////////////// MAP CONVERTION ////////////////////////////////
	// Singleton implementation for String-ENUM convertion, this help to all child classes access to transformation.

	// Initialize singlenton for all maps.
	static void InitializeConversionMaps();

	// Gets the StringToEnumMaterialMap
	EMaterial GetStringToEnumMaterialMap(const FString& materialString) const;

	// Gets the StringToEnumSizeMap
	ESize GetStringToEnumSizeMap(const FString& sizeString) const;

	// Gets the StringToEnumFormMap
	EForm GetStringToEnumFormMap(const FString& formString) const;

	// Gets the StringToEnumColorMap
	EColor GetStringToEnumColorMap(const FString& colorString) const;

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
