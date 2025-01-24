// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseStorage.h"

// Sets default values
ABaseStorage::ABaseStorage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseStorage::BeginPlay()
{
	Super::BeginPlay();

	GenerateRandomStock(); // Initialice Stock.

}

// Called every frame
void ABaseStorage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////////////////////////////////////////////////////////

// Checks if the Initial Piece configuration already exist on the map and add quantity, if not, creates a new entry.
void ABaseStorage::AddInitialPieceToMap(FInitialPieceAttribute newInitialPiece, int quantity)
{
	if(initialPieceMap.Contains(newInitialPiece))
	{
		initialPieceMap[newInitialPiece] += quantity;
	}else
	{
		initialPieceMap.Add(newInitialPiece, quantity);
	}

}

void ABaseStorage::DecreacePieceFromInventory(FInitialPieceAttribute pieceCode, int quantity)
{
	if(initialPieceMap.Contains(pieceCode))
	{
		initialPieceMap[pieceCode] -= quantity;
	}

}

// Checks in the Initial Piece inventory the order that needs to be ordered.
FStock ABaseStorage::GetStockOrders(FInitialPieceAttribute order)
{
	FStock orderAsked;
	orderAsked.orderInStock = initialPieceMap.Contains(order);
	if(initialPieceMap.Contains(order))
	{
		orderAsked.orderStockQuantity = initialPieceMap[order];
	}else
	{
		orderAsked.orderStockQuantity = 0;
	}

	return orderAsked;

}

// Returns the Piece Map inventory.
const TMap<FInitialPieceAttribute, int>& ABaseStorage::GetInventory() const
{
	return initialPieceMap;

}

// Called to ask for raw material.
void ABaseStorage::ReplenishStorage(int quantity, FString rawMaterialCode)
{
	FInitialPieceAttribute orderedProduct;

	orderedProduct.Quality = UEProductProperties::ConverStringToEnumQuality(rawMaterialCode.Left(2));
	orderedProduct.Size = UEProductProperties::ConverStringToEnumSize(rawMaterialCode.Mid(2, 2));
	orderedProduct.Length = UEProductProperties::ConverStringToEnumLength(rawMaterialCode.Right(2));

	AddInitialPieceToMap(orderedProduct, quantity);

}

// Randomice and store initial pieces to stock on Base Storage.
void ABaseStorage::GenerateRandomStock()
{
	int randomGeneratorIteration = (int)FMath::RandRange(10, 25); // 25, 30 are only a random numbers selected, it doesn't have a specific reason.
	for(int i = 0; i < randomGeneratorIteration; i++)
	{
		int randomIndex = (int)FMath::RandRange(1, 3);
        FInitialPieceAttribute orderGenerated;
        FString testStringOrder; /////////////////////////////
        switch (randomIndex)
        {
        case 1:
            orderGenerated.Quality = EPieceMaterial::QUALITY_LOW;
            testStringOrder = "M1"; /////////////////////////////
            break;

        case 2:
            orderGenerated.Quality = EPieceMaterial::QUALITY_MEDIUM;
            testStringOrder = "M2"; /////////////////////////////
            break;

        case 3:
            orderGenerated.Quality = EPieceMaterial::QUALITY_HIGH;
            testStringOrder = "M3"; /////////////////////////////
            break;
        
        default:
            break;
        }
        
        randomIndex = (int)FMath::RandRange(1, 3);
        switch (randomIndex)
        {
        case 1:
            orderGenerated.Size = EPieceSize::SIZE_SMALL;
            testStringOrder += "S1"; /////////////////////////////
            break;

        case 2:
            orderGenerated.Size = EPieceSize::SIZE_MEDIUM;
            testStringOrder += "S2"; /////////////////////////////
            break;

        case 3:
            orderGenerated.Size = EPieceSize::SIZE_BIG;
            testStringOrder += "S3"; /////////////////////////////
            break;
        
        default:
            break;
        }

        randomIndex = (int)FMath::RandRange(1, 3);
        switch (randomIndex)
        {
        case 1:
            orderGenerated.Length = EPieceLenght::LENGTH_SHORT;
            testStringOrder += "L1"; /////////////////////////////
            break;

        case 2:
            orderGenerated.Length = EPieceLenght::LENGTH_MEDIUM;
            testStringOrder += "L2"; /////////////////////////////
            break;

        case 3:
            orderGenerated.Length = EPieceLenght::LENGTH_LARGE;
            testStringOrder += "L3"; /////////////////////////////
            break;
        
        default:
            break;
        }

		int randomQuantityToAddOnStock = (int)FMath::RandRange(1, 5); // 5, 20 are only a random numbers selected, it doesn't have a specific reason.
		AddInitialPieceToMap(orderGenerated, randomQuantityToAddOnStock);
        UE_LOG(LogTemp, Display, TEXT("Stock Generated: %s, Quantity: %i"), *testStringOrder, randomQuantityToAddOnStock);
	}

}
