// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseStorage.h" // To access Enums and Struct
#include "StorageManager.generated.h"

UENUM(BlueprintType)
enum class EStorageProductionStatus : uint8
{
	CAN_PRODUCE,
	CANNOT_PRODUCE,
	FULL_PRODUCTION
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

	// Delegate event to Spawn order.
	FOnOrderProcessed orderToProcess;

	// Recieve a FString to convert into Enum. Returns False if not enough material or returns true othewise and trigger event for spawn product.
	EStorageProductionStatus CanProduceProductOrder(FString Order, int quantity);

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

};
