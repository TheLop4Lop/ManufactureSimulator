// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MachineQuality.generated.h"

UENUM(BlueprintType)
enum class EMachineQualityStatus : uint8
{
	POWER_OFF,
	BOX_EMPTY,
	NO_MATCH,
	MULTIPLE,
	SCANNED

};

UCLASS()
class MANOFACTURESIMULATOR_API AMachineQuality : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMachineQuality();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Change Power machine Status.
	void SetMachinePower();

	// Get the actual stage of the scanner machine.
	bool GetMachinePower();

	// Scan Produc inside de boxDetector.
	EMachineQualityStatus ScanForProduct();

	// Returns Proudct code from scannedProduct.
	FString GetProductCode();

	// Returns Product Quality status.
	float GetProductQuality();

protected:
	///////////////////////////////////// MACHINE PROPERTIES ////////////////////////////////
	// Section for the Machine Properties.

	// Machine Quality Static Mesh.
	UPROPERTY(EditAnywhere, Category = "Machine Properties", meta = (AllowPrivateAccess))
	UStaticMeshComponent* machineMesh;

	// Machine Product detector Box.
	UPROPERTY(EditAnywhere, Category = "Machine Properties", meta = (AllowPrivateAccess))
	class UBoxComponent* boxDetector;

	///////////////////////////////////// MACHINE PROCESS ////////////////////////////////
	// Section for the Machine Process.

	// Determines Machine Power Status.
	UPROPERTY(EditAnywhere, Category = "Machine Process", meta = (AllowPrivateAccess))
	bool isPowered;

	class ABaseProduct* scannedProduct;

	///////////////////////////////////// SCANNER SOUNDS ////////////////////////////////
	// Section for Scanner sounds.

	// Holds the reference to a SoundBase for PowerOn machine.
	UPROPERTY(EditAnywhere, Category = "Scanner Sounds", meta = (AllowPrivateAccess))
	USoundBase* scannerOnSound;

	// Holds the reference to a SoundBase for empty scanner.
	UPROPERTY(EditAnywhere, Category = "Scanner Sounds", meta = (AllowPrivateAccess))
	USoundBase* emptyScannerSound;

	// Holds the reference to a SoundBase for no piece detected on scanner.
	UPROPERTY(EditAnywhere, Category = "Scanner Sounds", meta = (AllowPrivateAccess))
	USoundBase* noPieceOnScannerSound;

	// Holds the reference to a SoundBase for multiple pieces detected on scanner.
	UPROPERTY(EditAnywhere, Category = "Scanner Sounds", meta = (AllowPrivateAccess))
	USoundBase* multiplePiecesOnScannerSound;

	// Holds the reference to a SoundBase for no piece detected on scanner.
	UPROPERTY(EditAnywhere, Category = "Scanner Sounds", meta = (AllowPrivateAccess))
	USoundBase* scannerActionSound;

	// Handles On audio Spawned in the world.
	class UAudioComponent* onAudioHandle;

};
