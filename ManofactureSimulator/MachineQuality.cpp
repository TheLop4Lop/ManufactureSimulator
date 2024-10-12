// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineQuality.h"
#include "Components/BoxComponent.h"
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
			return EMachineQualityStatus::BOX_EMPTY;
		}else if(actorsInBox.Num() > 1)
		{
			return EMachineQualityStatus::MULTIPLE;
		}else
		{
			if(!actorsInBox[0]->IsA(ABaseProduct::StaticClass()))
			{
				return EMachineQualityStatus::NO_MATCH;
			}else
			{
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
