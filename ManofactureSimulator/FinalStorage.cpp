// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalStorage.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"
#include "PaintedProduct.h"

// Sets default values
AFinalStorage::AFinalStorage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	storageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Storage"));
	RootComponent = storageBox;

}

// Called when the game starts or when spawned
void AFinalStorage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinalStorage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> actorsInside;
	storageBox->GetOverlappingActors(actorsInside);

	for(AActor* singleActor : actorsInside)
	{
		if(singleActor->IsA(APaintedProduct::StaticClass()))
		{
			APaintedProduct* productOnStorageEntrance = Cast<APaintedProduct>(singleActor);
			if(productOnStorageEntrance->IsProductFinished())
			{
				UE_LOG(LogTemp, Display, TEXT("STORING..."));
				pieceInStorage.ExecuteIfBound(productOnStorageEntrance->GetProductCode());
				if(finishedPiecesCodeInStorage.Contains(productOnStorageEntrance->GetProductCode()))
				{
					finishedPiecesCodeInStorage[productOnStorageEntrance->GetProductCode()] ++;
				}else
				{
					finishedPiecesCodeInStorage.Add(productOnStorageEntrance->GetProductCode(), 1);
				}
				totalProductsStored++;
				productOnStorageEntrance->Destroy();
			}
		}
	}

}

// Returns the total amount of product stored.
int AFinalStorage::GetTotalOfProductsStored()
{
	return totalProductsStored;

}

// Gets the most produced product during the simulation.
FString AFinalStorage::GetMostProducedCode()
{
	int maxValue = 0;
	FString mostProduced = "";

	for (const TPair<FString, int>& entryProduct : finishedPiecesCodeInStorage)
	{
		if(entryProduct.Value > maxValue)
		{
			maxValue = entryProduct.Value;
			mostProduced = entryProduct.Key;
		}
	}
	return mostProduced;

}
