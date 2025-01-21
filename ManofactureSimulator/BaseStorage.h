// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EProductProperties.h" // To get access to Product Properties ENUM.
#include "BaseStorage.generated.h"

USTRUCT(BlueprintType)
struct FInitialPieceAttribute
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPieceMaterial Quality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPieceSize Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPieceLenght Length;

	// Defult value constructor.
	FInitialPieceAttribute()
		: Quality(EPieceMaterial::QUALITY_LOW),
		  Size(EPieceSize::SIZE_SMALL),
		  Length(EPieceLenght::LENGTH_SHORT)
	{}

	// Operator overload, use for comparing if two keys are the same on the TMap.
	bool operator==(const FInitialPieceAttribute& otherPiece) const
	{
		return Quality == otherPiece.Quality && Size == otherPiece.Size && Length == otherPiece.Length;
	}

	// Determine where the FInitialPieceAttribute should be stored.
	friend uint32 GetTypeHash(const FInitialPieceAttribute& Key)
	{
		return HashCombine(HashCombine(GetTypeHash(static_cast<uint8>(Key.Quality)), GetTypeHash(static_cast<uint8>(Key.Size))), GetTypeHash(static_cast<uint8>(Key.Length)));
	}

};

USTRUCT(BlueprintType)
struct FStock
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool orderInStock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int orderStockQuantity;

};

UCLASS()
class MANOFACTURESIMULATOR_API ABaseStorage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseStorage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//////////////////////////////////////////////////////////////////
	// Checks if the Initial Piece configuration already exist on the map and add quantity, if not, creates a new entry.
	void AddInitialPieceToMap(FInitialPieceAttribute newInitialPiece, int quantity);

	void DecreacePieceFromInventory(FInitialPieceAttribute pieceCode, int quantity);

	// Checks in the Initial Piece inventory the order that needs to be ordered.
	FStock GetStockOrders(FInitialPieceAttribute order);

	// Returns the Piece Map inventory.
	const TMap<FInitialPieceAttribute, int>& GetInventory() const;

	// Called to ask for raw material.
	void ReplenishStorage(int quantity, FString rawMaterialCode);

	// Randomice and store initial pieces to stock on Base Storage.
	void GenerateRandomStock();

private:
	///////////////////////////////////// STORAGE PIECE SETTINGS ////////////////////////////////
	// Section for all inventory variables.

	// TMap that holds the iterations of the Initial Piece and how many they are.
	TMap<FInitialPieceAttribute, int> initialPieceMap;

};
