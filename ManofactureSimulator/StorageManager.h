// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseStorage.h" // To access Enums and Struct
#include "StorageManager.generated.h"

DECLARE_DELEGATE(FOrderDelivered)
DECLARE_DELEGATE_TwoParams(FOrderStored, FString, bool)
DECLARE_DELEGATE_OneParam(FOrderOfTheDayStatusOnStock, TArray<FOrderInfo>)

UENUM(BlueprintType)
enum class EStorageProductionStatus : uint8
{
	CAN_PRODUCE,
	CANNOT_PRODUCE,
	FULL_PRODUCTION,
	NO_PRODUCT_STOCKED
	
};

USTRUCT(BlueprintType)
struct FProductQuantity
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FInitialPieceAttribute codeProduct;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int quantity;

	FProductQuantity()
		: codeProduct(), quantity(0)
	{}

	FProductQuantity(FInitialPieceAttribute InCode, int InQuantity)
        : codeProduct(InCode), quantity(InQuantity)
    {}

};

USTRUCT(BlueprintType)
struct FOrdersForProduction
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int orderForProductionQuantity = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString orderForProductionCode;

};

USTRUCT(BlueprintType)
struct FOrdersInLengthMaterial
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int l1Quantity = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int l2Quantity = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int l3Quantity = 0;

};

USTRUCT(BlueprintType)
struct FOrderInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EStorageProductionStatus orderStatusInfoEnum;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FOrdersInLengthMaterial orderLenghtsInfo;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int totalAmountOfPieceFromStock = 0;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOrderProcessed, FInitialPieceAttribute, ProductID, int, Quantity);

UCLASS()
class MANOFACTURESIMULATOR_API AStorageManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStorageManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Delegate event to signal an order has been delivered.
	FOrderDelivered orderDelivered;

	// Delegate event to Spawn order.
	FOnOrderProcessed orderToProcess;

	// Delegate that execute an orders stored to be counted on Manager Computer for sell.
	FOrderStored orderStored;

	// Delegate for passing on the Status on Orders of the day for player interpretation.
	FOrderOfTheDayStatusOnStock statusOnStock;

	// Recieve a FString to convert into Enum. Returns False if not enough material or returns true othewise and trigger event for spawn product.
	EStorageProductionStatus CanProduceProductOrder(FString Order, int quantity);

	// Gets the quaintity of pieces produced stored in Final Storage.
	int GetTotalAmountOfProducedProducts();

	// Called to ask for raw material.
	void ReplenishRawMaterial(int quantity, FString rawMaterialCode);

	// Gets the orders of the day for production follow up.
	void GetOrdersOfTheDay(TArray<FOrdersForProduction> ordersSelectedDay);

	// Get the Max produced code by the player.
	FString GetMaxProducedCode();

protected:
	///////////////////////////////////// STORAGE/SPAWNER REFERENCES ////////////////////////////////
	// Section for Storages references

	// Reference in world of Base Storage, responsable of holding raw material for production.
	class ABaseStorage* baseStorage;
	// Reference in world of Final Storage, responsable of holding produced materials by producton.
	class AFinalStorage* finalStorage;

	// Reference in the world of PieceSpawner, responsable of spawning product.
	class APieceSpawner* productSpawner;

	///////////////////////////////////// PRODUCT QUANTITY MANAGER ////////////////////////////////
	// Section manages the order quantity the player can make.

	// Holds the max quantity of orders.
	UPROPERTY(EditAnywhere, Category = "Product Order Manager", meta = (AllowPrivateAccess))
	int maxProductOrder = 5;

	// Timer for handle Raw Piece Spawn.
	FTimerHandle spawnTimer;

	// Holds the orders to spawn.
	TArray<FProductQuantity> ordersToSpawn;

	// First check if exit is clear and then calls SpawnProductOrder.
	void TryToSpawnProduct();

	// Spawn product.
	void SpawnProductOrder();

	///////////////////////////////////// PRODUCT QUANTITY MANAGER ////////////////////////////////
	// Section manages the order quantity the player can make.

	// Holds the order of the day selected by player. I will compare a product on Final Store for processing or for storage.
	TArray<FOrdersForProduction> ordersOfTheDay;

	// Holds the specification of order quantity, Lenght pieces and status in stock for each order fo the day.
	TArray<FOrderInfo> ordersOfTheDayInfo;

	// Called to check order in Final Storage to sell on Manager Computer.
	void CheckOrderInOrdersOfTheDay(FString storedOrder);

	// Updated the stock information for player interpretation.
	void UpdateOrdersOfTheDayOnStock();

	// With the Order of the Day check in stock if has the necessary materials for production.
	FOrdersInLengthMaterial ConvertQuantityProductionOrderToStock(int orderQuantityOnStock);

	void SetOrderInfo(FOrdersInLengthMaterial orderQuantityAsked, FOrderInfo* orderInfo, FString productionCode, FString lengthCode);

};
