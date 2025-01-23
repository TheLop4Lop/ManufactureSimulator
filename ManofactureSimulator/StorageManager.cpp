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

	if(baseStorage)
	{
		FStock productDisponibility = baseStorage->GetStockOrders(productToOrder);
		if(productDisponibility.orderInStock)
		{
			if(productDisponibility.orderStockQuantity >= quantity && (ordersToSpawn.Num() < maxProductOrder)) // For Spawning material from Base Storage.
			{
				UE_LOG(LogTemp, Display, TEXT("ENOUGH FOR PRODUCT: %s"), *Order);
				FProductQuantity productToSpawn(productToOrder, quantity);
				ordersToSpawn.Add(productToSpawn);
				baseStorage->DecreacePieceFromInventory(ordersToSpawn[0].codeProduct, quantity);

				return EStorageProductionStatus::CAN_PRODUCE;
			}else if(!(productDisponibility.orderStockQuantity >= quantity)) // No enough product to produce order.
			{
				UE_LOG(LogTemp, Display, TEXT("NOT ENOUGH FOR PRODUCT: %s"), *Order);
				return EStorageProductionStatus::CANNOT_PRODUCE;
			}
		}else if (ordersToSpawn.Num() >= maxProductOrder) // Limit spawn order to Base Storage.
		{
			UE_LOG(LogTemp, Display, TEXT("STILL PROCESSING THE FIRST ONES"));
			return EStorageProductionStatus::FULL_PRODUCTION;
		}
	}

	return EStorageProductionStatus::NO_PRODUCT_STOCKED;

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
		if(ordersOfTheDay.Num() > 0)
		{
			UpdateOrdersOfTheDayOnStock(); // Updates the information on player after replenish the storage.
		}
	}

}

///////////////////////////////////// PRODUCT QUANTITY MANAGER ////////////////////////////////
// Section manages the order quantity the player can make.

// Gets the orders of the day for production follow up.
void AStorageManager::GetOrdersOfTheDay(TArray<FOrdersForProduction> ordersSelectedDay)
{
	for(int i = 0; i < ordersSelectedDay.Num(); i++)
	{
		ordersOfTheDay.Add(ordersSelectedDay[i]);
	}
	UpdateOrdersOfTheDayOnStock();

}

// Updated the stock information for player interpretation.
void AStorageManager::UpdateOrdersOfTheDayOnStock()
{
	const int piecesPerL3 = 10; // 10 is the quantity amout of pieces the Cutter Machine can cut from an L3 initial log.
    const int piecesPerL2 = 5; // 5 is the quantity amout of pieces the Cutter Machine can cut from an L2 initial log.
    const int piecesPerL1 = 3; // 3 is the quantity amout of pieces the Cutter Machine can cut from an L1 initial log.

	for(int i = 0; i < ordersOfTheDay.Num(); i++)
	{
		FOrdersInLengthMaterial orderLengthStock = ConvertQuantityProductionOrderToStock(ordersOfTheDay[i].orderForProductionQuantity);
		FOrderInfo orderOnstockStatus; // To add in ordersOfTheDayInfo TArray to pass to Character info.

		if(baseStorage)
		{
			if(orderLengthStock.l1Quantity > 0)
			{
				const FString l1Code = "L1";
				SetOrderInfo(orderLengthStock, &orderOnstockStatus, ordersOfTheDay[i].orderForProductionCode, l1Code);
			}

			if(orderLengthStock.l2Quantity > 0)
			{
				const FString l2Code = "L2";
				SetOrderInfo(orderLengthStock, &orderOnstockStatus, ordersOfTheDay[i].orderForProductionCode, l2Code);
			}

			if(orderLengthStock.l3Quantity > 0)
			{
				const FString l3Code = "L3";
				SetOrderInfo(orderLengthStock, &orderOnstockStatus, ordersOfTheDay[i].orderForProductionCode, l3Code);
			}
		}
		orderOnstockStatus.totalAmountOfPieceFromStock = (orderOnstockStatus.orderLenghtsInfo.l1Quantity * piecesPerL1) + 
															(orderOnstockStatus.orderLenghtsInfo.l2Quantity * piecesPerL2) +
																(orderOnstockStatus.orderLenghtsInfo.l3Quantity * piecesPerL3);
		ordersOfTheDayInfo.Add(orderOnstockStatus);
	}
	statusOnStock.ExecuteIfBound(ordersOfTheDayInfo);

}

// Called to check order in Final Storage to sell on Manager Computer.
void AStorageManager::CheckOrderInOrdersOfTheDay(FString storedOrder)
{
	for(FOrdersForProduction singleOrder : ordersOfTheDay)
	{
		if(singleOrder.orderForProductionCode.Equals(storedOrder))
		{
			orderStored.ExecuteIfBound(storedOrder);
		}
	}

}

// With the Order of the Day check in stock if has the necessary materials for production.
FOrdersInLengthMaterial AStorageManager::ConvertQuantityProductionOrderToStock(int orderQuantityOnStock)
{
	FOrdersInLengthMaterial totalLengthOrders;

    const int piecesPerL3 = 10; // 10 is the quantity amout of pieces the Cutter Machine can cut from an L3 initial log.
    const int piecesPerL2 = 5; // 5 is the quantity amout of pieces the Cutter Machine can cut from an L2 initial log.
    const int piecesPerL1 = 3; // 3 is the quantity amout of pieces the Cutter Machine can cut from an L1 initial log.

	int totalPiecesL3 = 0;
	int totalPiecesL2 = 0;
	int totalPiecesL1 = 0;

	totalPiecesL3 += FMath::FloorToInt(orderQuantityOnStock / piecesPerL3);
	orderQuantityOnStock %= piecesPerL3;

	switch (orderQuantityOnStock)
	{
	case 9:
		totalPiecesL2 += 2;
		break;

	case 8:
	case 7:
	case 6:
		totalPiecesL2 += 1;
		totalPiecesL1 += 1;
		break;

	case 5:
	case 4:
		totalPiecesL2 += 1;
		break;

	case 3:
	case 2:
	case 1:
		totalPiecesL1 += 1;
		break;

	default:
		break;
	}

	totalLengthOrders.l1Quantity = totalPiecesL1;
	totalLengthOrders.l2Quantity = totalPiecesL2;
	totalLengthOrders.l3Quantity = totalPiecesL3;

	return totalLengthOrders;

}

void AStorageManager::SetOrderInfo(FOrdersInLengthMaterial orderQuantityAsked, FOrderInfo* orderInfo, FString productionCode, FString lengthCode)
{
	if(orderInfo)
	{
		FInitialPieceAttribute productOnStock;

		productOnStock.Quality = UEProductProperties::ConverStringToEnumQuality(productionCode.Left(2));
		productOnStock.Size = UEProductProperties::ConverStringToEnumSize(productionCode.Mid(2,2));
		productOnStock.Length = UEProductProperties::ConverStringToEnumLength(lengthCode);

		FStock productOnStockAvailability = baseStorage->GetStockOrders(productOnStock);
		FOrdersInLengthMaterial lengthMaterialsInStock;

		switch (UEProductProperties::ConverStringToEnumLength(lengthCode))
		{
		case EPieceLenght::LENGTH_SHORT:
			if(productOnStockAvailability.orderInStock) // Enters if order in format MxSxL1 is in stock.
			{
				if(productOnStockAvailability.orderStockQuantity >= orderQuantityAsked.l1Quantity) // Enters if there are enough orders in stock for ptoduction.
				{
					orderInfo->orderStatusInfoEnum = EStorageProductionStatus::CAN_PRODUCE;
				}else // No enough product to produce order.
				{
					orderInfo->orderStatusInfoEnum = EStorageProductionStatus::CANNOT_PRODUCE;
				}
				lengthMaterialsInStock.l1Quantity = productOnStockAvailability.orderStockQuantity;
			}else
			{
				orderInfo->orderStatusInfoEnum = EStorageProductionStatus::NO_PRODUCT_STOCKED;
				lengthMaterialsInStock.l1Quantity = 0;
			}
			break;

		case EPieceLenght::LENGTH_MEDIUM:
			if(productOnStockAvailability.orderInStock) // Enters if order in format MxSxL2 is in stock.
			{
				if(productOnStockAvailability.orderStockQuantity >= orderQuantityAsked.l2Quantity) // Enters if there are enough orders in stock for ptoduction.
				{
					orderInfo->orderStatusInfoEnum = EStorageProductionStatus::CAN_PRODUCE;
				}else // No enough product to produce order.
				{
					orderInfo->orderStatusInfoEnum = EStorageProductionStatus::CANNOT_PRODUCE;
				}
				lengthMaterialsInStock.l2Quantity = productOnStockAvailability.orderStockQuantity;
			}else
			{
				orderInfo->orderStatusInfoEnum = EStorageProductionStatus::NO_PRODUCT_STOCKED;
				lengthMaterialsInStock.l2Quantity = 0;
			}
			break;

		case EPieceLenght::LENGTH_LARGE:
			if(productOnStockAvailability.orderInStock) // Enters if order in format MxSxL3 is in stock.
			{
				if(productOnStockAvailability.orderStockQuantity >= orderQuantityAsked.l3Quantity) // Enters if there are enough orders in stock for ptoduction.
				{
					orderInfo->orderStatusInfoEnum = EStorageProductionStatus::CAN_PRODUCE;
				}else // No enough product to produce order.
				{
					orderInfo->orderStatusInfoEnum = EStorageProductionStatus::CANNOT_PRODUCE;
				}
				lengthMaterialsInStock.l3Quantity = productOnStockAvailability.orderStockQuantity;
			}else
			{
				orderInfo->orderStatusInfoEnum = EStorageProductionStatus::NO_PRODUCT_STOCKED;
				lengthMaterialsInStock.l3Quantity = 0;
			}
			break;

		default:
			break;
		}
		orderInfo->orderLenghtsInfo.l1Quantity += lengthMaterialsInStock.l1Quantity;
		orderInfo->orderLenghtsInfo.l2Quantity += lengthMaterialsInStock.l2Quantity;
		orderInfo->orderLenghtsInfo.l3Quantity += lengthMaterialsInStock.l3Quantity;
	}

}
