// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineQuality.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BaseProduct.h"

// Sets default values
AMachineQuality::AMachineQuality()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	machineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Machine Quality Mesh"));
	RootComponent = machineMesh;

	boxDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("Product Detector"));
	boxDetector->SetupAttachment(machineMesh);

}

// Called when the game starts or when spawned
void AMachineQuality::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMachineQuality::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Change Power machine Status.
void AMachineQuality::SetMachinePower()
{
	isPowered = !isPowered;
	if(isPowered && scannerOnSound)
	{
		onAudioHandle = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), scannerOnSound, GetActorLocation());
	}else
	{
		onAudioHandle->Stop();
	}

}

// Get the actual stage of the scanner machine.
bool AMachineQuality::GetMachinePower()
{
	return isPowered;

}

// Scan Produc inside de boxDetector.
EMachineQualityStatus AMachineQuality::ScanForProduct()
{
	if(isPowered)
	{
		UE_LOG(LogTemp, Display, TEXT("Scanning..."));
		TArray<AActor*> actorsInBox;
		boxDetector->GetOverlappingActors(actorsInBox);

		if(actorsInBox.Num() == 0)
		{
			if(emptyScannerSound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), emptyScannerSound, GetActorLocation());
			return EMachineQualityStatus::BOX_EMPTY;
		}else if(actorsInBox.Num() > 1)
		{
			if(multiplePiecesOnScannerSound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), multiplePiecesOnScannerSound, GetActorLocation());
			return EMachineQualityStatus::MULTIPLE;
		}else
		{
			if(!actorsInBox[0]->IsA(ABaseProduct::StaticClass()))
			{
				if(noPieceOnScannerSound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), noPieceOnScannerSound, GetActorLocation());
				return EMachineQualityStatus::NO_MATCH;
			}else
			{
				if(scannerActionSound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), scannerActionSound, GetActorLocation());
				scannedProduct = Cast<ABaseProduct>(actorsInBox[0]);
				return EMachineQualityStatus::SCANNED;
			}
		}
	}

	return EMachineQualityStatus::POWER_OFF;

}

// Returns Proudct code from scannedProduct.
FString AMachineQuality::GetProductCode()
{
	if(scannedProduct)
	{
		return scannedProduct->GetProductCode();
	}

	return "";

}

// Returns Product Quality status.
float AMachineQuality::GetProductQuality()
{
	if(scannedProduct)
	{
		return (float)scannedProduct->GetProductQuality();
	}

	return 0;

}
