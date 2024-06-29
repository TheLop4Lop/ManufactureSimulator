// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <map>
#include <string>
#include "BaseMachine.generated.h"

UENUM(BlueprintType)
enum class EMachineStatus : uint8
{
	ON_MAINTENANCE,
	ON_PRODUCTION,
	ON_HOLD,
	FULL_PRODUCTION,
	CODE_ERROR

};

UENUM(BlueprintType)
enum class EProductMaterial : uint8 
{
	M1,
	M2,
	M3

};

UENUM(BlueprintType)
enum class EProductSize : uint8
{
	S1,
	S2,
	S3

};

UENUM(BlueprintType)
enum class EProductForm : uint8
{
	F1,
	F2,
	F3

};

UENUM(BlueprintType)
enum class EProductColor : uint8
{
	C1,
	C2,
	C3

};

USTRUCT(BlueprintType)
struct FProductColor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProductMaterial Quality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProductSize Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProductForm Form;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProductColor Color;

	FProductColor()
		: Quality(EProductMaterial::M1),
          Size(EProductSize::S1),
          Form(EProductForm::F1),
		  Color(EProductColor::C1)
	{}

};

UCLASS()
class MANOFACTURESIMULATOR_API ABaseMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	///////////////////////////////////// MAP CONVERTION ////////////////////////////////
	// Singleton implementation for String-ENUM convertion, this help to all child classes access to transformation.

	// Static MATERIAL map for string to ENUM data, this is used for product interpretation in respective machine.
	static std::map<FString, EProductMaterial> StringToEnumMaterialMap;

	// Static SIZE map for string to ENUM data, this is used for product interpretation in respective machine.
	static std::map<FString, EProductSize> StringToEnumSizeMap;

	// Static FORM map for string to ENUM data, this is used for product interpretation in respective machine.
	static std::map<FString, EProductForm> StringToEnumFormMap;

	// Static COLOR map for string to ENUM data, this is used for product interpretation in respective machine.
	static std::map<FString, EProductColor> StringToEnumColorMap;

protected:
	///////////////////////////////////// MAP CONVERTION ////////////////////////////////
	// Singleton implementation for String-ENUM convertion, this help to all child classes access to transformation.

	// Initialize singlenton for all maps.
	static void InitializeConversionMaps();

	// Gets the StringToEnumMaterialMap
	EProductMaterial GetStringToEnumMaterialMap(const FString& materialString) const;

	// Gets the StringToEnumSizeMap
	EProductSize GetStringToEnumSizeMap(const FString& sizeString) const;

	// Gets the StringToEnumFormMap
	EProductForm GetStringToEnumFormMap(const FString& formString) const;

	// Gets the StringToEnumColorMap
	EProductColor GetStringToEnumColorMap(const FString& colorString) const;

	///////////////////////////////////// MACHINE PROPERTIES ////////////////////////////////
	// Section for all the machine initial properties.

	// Machinery Mesh
	UPROPERTY(EditAnywhere, Category = "Machine Properties", meta = (AllowPrivateAccess))
	UStaticMeshComponent* machineMesh;

	// Machine Computer Mesh
	UPROPERTY(EditAnywhere, Category = "Machine Properties", meta = (AllowPrivateAccess))
	UStaticMeshComponent* computerMesh;

	// Box Entrance that manages the product and determines it properties and actions.
	UPROPERTY(EditAnywhere, Category = "Machine Properties", meta = (AllowPrivateAccess))
	class UBoxComponent* boxEntrance;

	// Light Status for machine.
	UPROPERTY(EditAnywhere, Category = "Machine Properties", meta = (AllowPrivateAccess))
	class UPointLightComponent* machineStatusLight;

	// Arrow for spawn location and rotation of the objects.
	UPROPERTY(EditAnywhere, Category = "Machine Capacity", meta = (AllowPrivateAccess))
	class UArrowComponent* spawnArrow;

	// Holds reference to conveyor belt that provides product for production.
	class ABaseConveyorBelt* entranceConveyor;

	///////////////////////////////////// STATUS PROPERTIES ////////////////////////////////
	// Main varibles that controll the machine mechanic.

	// Set power machine status.
	UPROPERTY(EditAnywhere, Category = "Status Properties", meta = (AllowPrivateAccess))
	bool isPowered;

	// Sets if the machine has been properly heathed, this is set by a timer after getting power.
	UPROPERTY(EditAnywhere, Category = "Status Properties", meta = (AllowPrivateAccess))
	bool isReady;

	// Sets the machine in Pause mode, this is for wait new instructions on the Widget.
	UPROPERTY(EditAnywhere, Category = "Status Properties", meta = (AllowPrivateAccess))
	bool isOnHold;

	// Sets maintenance status of the machine. Can't produce if this is on.
	UPROPERTY(EditAnywhere, Category = "Status Properties", meta = (AllowPrivateAccess))
	bool isInMaintenance;

	// Holds the actual status of the machine, this is then interpreted by a light color.
	UPROPERTY(EditAnywhere, Category = "Status Properties", meta = (AllowPrivateAccess))
	EMachineStatus productionStatus;

	// Checks the conditions of power machine and changes status for production.
	void SetInitialMachineStatus();

	// Sets ready status to true and clears timer.
	void SetReadyMachineStatus();
	// Sets ready status to false and clears timer.
	void ResetReadyMachineStatus();

	///////////////////////////////////// PRODUCT PROCESS ////////////////////////////////
	// Section for all the logic in process the product.

	// Holds the max quantity of orders.
	UPROPERTY(EditAnywhere, Category = "Machine Capacity", meta = (AllowPrivateAccess))
	int maxProductOrder = 5;

	// Quantity of Products entered to the machine.
	UPROPERTY(EditAnywhere, Category = "Machine Capacity", meta = (AllowPrivateAccess))
	int productsEntered;

	// Quantity of products produced.
	UPROPERTY(EditAnywhere, Category = "Machine Capacity", meta = (AllowPrivateAccess))
	int productsProduced;

	// Product class to transform. This will depend on the type of machine.
	UPROPERTY(EditAnywhere, Category = "Machine Capacity", meta = (AllowPrivateAccess))
	TSubclassOf<class ABaseProduct> classToTransform;

	// Holds the reference to the products that had enter the machine.
	UPROPERTY(EditAnywhere, Category = "Machine Capacity", meta = (AllowPrivateAccess))
	int productsToProcess;

	// Checks the actors on the boxEntrance, this will change depending on the machine.
	virtual void CheckEntranceForProduct();

	// Changes the production status light and actions.
	void ChangeProductionStatus(EMachineStatus newStatus);

	///////////////////////////////////// PRODUCTION TIMES ////////////////////////////////
	// Production times to spawn produced piece and get machine ready.

	// Sets the warm up time for the machine to be rady for production, this depends on the machine type.
	UPROPERTY(EditAnywhere, Category = "Production Time", meta = (AllowPrivateAccess))
	float machineWarmUp;

	// Sets the warm up time for the machine to be rady for production, this depends on the machine type.
	UPROPERTY(EditAnywhere, Category = "Production Time", meta = (AllowPrivateAccess))
	float machineWarmDown;
	
	// Sets the Maintenance time for the machine to be ready to produce again, this depends on the machine type.
	UPROPERTY(EditAnywhere, Category = "Production Time", meta = (AllowPrivateAccess))
	float maintenanceTime;

	// Holds the value of time consumed working on material type.
	UPROPERTY(EditAnywhere, Category = "Production Time", meta = (AllowPrivateAccess))
	float timeByMaterialLow;

	// Holds the value of time consumed working on material type.
	UPROPERTY(EditAnywhere, Category = "Production Time", meta = (AllowPrivateAccess))
	float timeByMaterialMidd;

	// Holds the value of time consumed working on material type.
	UPROPERTY(EditAnywhere, Category = "Production Time", meta = (AllowPrivateAccess))
	float timeByMaterialHigh;

	float timeByMaterial;
	
	// Holds the value of the time consumed working with the size of the product.
	UPROPERTY(EditAnywhere, Category = "Production Time", meta = (AllowPrivateAccess))
	float timeBySizeLow;

	// Holds the value of the time consumed working with the size of the product.
	UPROPERTY(EditAnywhere, Category = "Production Time", meta = (AllowPrivateAccess))
	float timeBySizeMidd;

	// Holds the value of the time consumed working with the size of the product.
	UPROPERTY(EditAnywhere, Category = "Production Time", meta = (AllowPrivateAccess))
	float timeBySizeHigh;

	float timeBySize;

	// Holds the value of the time consumed working on form on product.
	UPROPERTY(EditAnywhere, Category = "Production Time", meta = (AllowPrivateAccess))
	float timeByFormF1;

	// Holds the value of the time consumed working on form on product.
	UPROPERTY(EditAnywhere, Category = "Production Time", meta = (AllowPrivateAccess))
	float timeByFormF2;

	// Holds the value of the time consumed working on form on product.
	UPROPERTY(EditAnywhere, Category = "Production Time", meta = (AllowPrivateAccess))
	float timeByFormF3;

	float timeByForm;

	// Holds the value of the time comsumed working on the color of the product.
	UPROPERTY(EditAnywhere, Category = "Production Time", meta = (AllowPrivateAccess))
	float timeByColorC1;

	// Holds the value of the time comsumed working on the color of the product.
	UPROPERTY(EditAnywhere, Category = "Production Time", meta = (AllowPrivateAccess))
	float timeByColorC2;

	// Holds the value of the time comsumed working on the color of the product.
	UPROPERTY(EditAnywhere, Category = "Production Time", meta = (AllowPrivateAccess))
	float timeByColorC3;

	float timeByColor;

	// Holds the value of the time comsumed working on the color of the product.
	UPROPERTY(EditAnywhere, Category = "Production Time", meta = (AllowPrivateAccess))
	float totalProductionPerPiece;
	
	// Timer for handle initial ready up timer for machine.
	FTimerHandle processTimer;

	// Timer for handle Raw Piece Spawn and initial ready up timer for machine.
	FTimerHandle spawnTimer;

	///////////////////////////////////// SPAWN PRODUCT ////////////////////////////////
	// Section for spawn product and set properties.

	// Holds different mesh for product.
	UPROPERTY(EditAnywhere, Category = "Spawn Product", meta = (AllowPrivateMessage))
	TArray<UStaticMesh*> productMesh;

	// Holds different FVector values for sizes.
	UPROPERTY(EditAnywhere, Category = "Spawn Product", meta = (AllowPrivateMessage))
	TArray<FVector> productSize;

	// Holds different quality materials for product.
	UPROPERTY(EditAnywhere, Category = "Spawn Product", meta = (AllowPrivateMessage))
	TArray<UMaterial*> qualityMaterial;

	// Class for ABaseProduct childs to spawn.
	UPROPERTY(EditAnywhere, Category = "Spawn Product", meta = (AllowPrivateAccess))
	TSubclassOf<class ABaseProduct> productClass;

	// Checks all the conditions for spawn a product and spawn it.
	void CheckConditionsForSpawnProduct();

	// Spawn product based on a specific ABaseProduct child, dependes on the process and machine.
	virtual void SpawnProducedProduct();

};
