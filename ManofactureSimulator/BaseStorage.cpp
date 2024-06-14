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
	
	FInitialPieceAttribute testProduct;
	testProduct.Quality = EMaterialQuality::QUALITY_LOW;
	testProduct.Size = EMaterialSize::SIZE_MEDIUM;
	testProduct.Length = EMaterialLength::LENGTH_LARGE;

	AddInitialPieceToMap(testProduct, 10);

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
bool ABaseStorage::OrderIsInInventory(FInitialPieceAttribute order, int quantity)
{
	return (initialPieceMap.Contains(order) && initialPieceMap[order] >= quantity);

}

// Returns the Piece Map inventory.
const TMap<FInitialPieceAttribute, int>& ABaseStorage::GetInventory() const
{
	return initialPieceMap;

}
