// Fill out your copyright notice in the Description page of Project Settings.

#include "StorageManager.h"
#include "Runtime/Core/Public/Misc/CString.h"
#include "Kismet/GameplayStatics.h"
#include "EProductProperties.h" // To get access to Product Properties ENUM.
#include "PieceSpawner.h"
#include "FinalStorage.h"
#include "BaseStorage.h"

// Sets default values
AStorageManager::AStorageManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStorageManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseStorage::StaticClass(), actorsInWorld);
	if (actorsInWorld.IsValidIndex(0)) baseStorage = Cast<ABaseStorage>(actorsInWorld[0]);

	actorsInWorld.Empty();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFinalStorage::StaticClass(), actorsInWorld);
	if (actorsInWorld.IsValidIndex(0)) finalStorage = Cast<AFinalStorage>(actorsInWorld[0]);

	if(finalStorage) finalStorage->pieceInStorage.BindUObject(this, &AStorageManager::CheckOrderInOrdersOfTheDay);

	actorsInWorld.Empty();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APieceSpawner::StaticClass(), actorsInWorld);
	if (actorsInWorld.IsValidIndex(0)) productSpawner = Cast<APieceSpawner>(actorsInWorld[0]);
}

// Called every frame
void AStorageManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetWorldTimerManager().IsTimerActive(spawnTimer) && ordersToSpawn.Num() > 0)
	{
		GetWorldTimerManager().SetTimer(spawnTimer, this, &AStorageManager::TryToSpawnProduct, 5.0f, true);
	}

}

// Recieve a FString to convert into Enum. Returns False if not enough material or returns true othewise and trigger event for spawn product.
EStorageProductionStatus AStorageManager::CanProduceProductOrder(FString Order, int quantity)
{
	FInitialPieceAttribute productToOrder;

	productToOrder.Quality = UEProductProperties::ConverStringToEnumQuality(Order.Left(2));
	productToOrder.Size = UEProductProperties::ConverStringToEnumSize(Order.Mid(2,2));
	productToOrder.Length = UEProductProperties::ConverStringToEnumLength(Order.Right(2));

	if (baseStorage->OrderIsInInventory(productToOrder, quantity) && (ordersToSpawn.Num() < maxProductOrder))
	{
		UE_LOG(LogTemp, Display, TEXT("ENOUGH FOR PRODUCT: %s"), *Order);
		FProductQuantity productToSpawn(productToOrder, quantity);
		ordersToSpawn.Add(productToSpawn);
		baseStorage->DecreacePieceFromInventory(ordersToSpawn[0].codeProduct, quantity);

		return EStorageProductionStatus::CAN_PRODUCE;
	}
	else if (ordersToSpawn.Num() >= maxProductOrder)
	{
		UE_LOG(LogTemp, Display, TEXT("STILL PROCESSING THE FIRST ONES"));
		return EStorageProductionStatus::FULL_PRODUCTION;
	}

	UE_LOG(LogTemp, Display, TEXT("NOT ENOUGH FOR PRODUCT: %s"), *Order);
	return EStorageProductionStatus::CANNOT_PRODUCE;

}

void AStorageManager::TryToSpawnProduct()
{
	if(productSpawner->CheckClearExit())
	{
		SpawnProductOrder();
	}

}

void AStorageManager::SpawnProductOrder()
{
	if (ordersToSpawn.Num() > 0)
	{
		if (ordersToSpawn[0].quantity == 0)
		{
			ordersToSpawn.RemoveAt(0);
			if (ordersToSpawn.Num() == 0)
			{
				GetWorldTimerManager().ClearTimer(spawnTimer);
				return;
			}
		}
		else
		{
			productSpawner->SpawnInitialPiece(ordersToSpawn[0].codeProduct);
			ordersToSpawn[0].quantity--;
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(spawnTimer);
	}

}

// Gets the quaintity of pieces produced stored in Final Storage.
int AStorageManager::GetTotalAmountOfProducedProducts()
{
	if(finalStorage)
	{
		return finalStorage->GetTotalOfProductsStored();
	}

	return 0;
	
}

// Called to ask for raw material.
void AStorageManager::ReplenishRawMaterial(int quantity, FString rawMaterialCode)
{
	if(baseStorage)
	{
		baseStorage->ReplenishStorage(quantity, rawMaterialCode);
	}

}

///////////////////////////////////// PRODUCT QUANTITY MANAGER ////////////////////////////////
// Section manages the order quantity the player can make.

// Gets the orders of the day for production follow up.
void AStorageManager::GetOrdersOfTheDay(TArray<FString> ordersSelectedDay)
{
	for(int i = 0; i < ordersSelectedDay.Num(); i++)
	{
		ordersOfTheDay.Add(ordersSelectedDay[i]);
	}

}

// Called to check order in Final Storage to sell on Manager Computer.
void AStorageManager::CheckOrderInOrdersOfTheDay(FString storedOrder)
{
	UE_LOG(LogTemp, Display, TEXT("CHECKING ORDER WITH OOTD..."));
	for(FString singleOrder : ordersOfTheDay)
	{
		if(singleOrder.Equals(storedOrder))
		{
			UE_LOG(LogTemp, Display, TEXT("CHECKED!"));
			orderStored.ExecuteIfBound(storedOrder);
		}
	}

}
