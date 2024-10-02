// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseStorage.generated.h"

UENUM(BlueprintType)
enum class EMaterialQuality : uint8
{
	QUALITY_LOW,
	QUALITY_MEDIUM,
	QUALITY_HIGH
};

UENUM(BlueprintType)
enum class EMaterialSize : uint8
{
	SIZE_SMALL,
	SIZE_MEDIUM,
	SIZE_BIG
};

UENUM(BlueprintType)
enum class EMaterialLength : uint8
{
	LENGTH_SHORT,
	LENGTH_MEDIUM,
	LENGTH_LARGE
};

USTRUCT(BlueprintType)
struct FInitialPieceAttribute
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMaterialQuality Quality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMaterialSize Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMaterialLength Length;

	// Defult value constructor.
	FInitialPieceAttribute()
		: Quality(EMaterialQuality::QUALITY_LOW),
		  Size(EMaterialSize::SIZE_SMALL),
		  Length(EMaterialLength::LENGTH_SHORT)
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
	bool OrderIsInInventory(FInitialPieceAttribute order, int quantity);

	// Returns the Piece Map inventory.
	const TMap<FInitialPieceAttribute, int>& GetInventory() const;

private:
	///////////////////////////////////// STORAGE PIECE SETTINGS ////////////////////////////////
	// Section for all inventory variables.

	// TMap that holds the iterations of the Initial Piece and how many they are.
	TMap<FInitialPieceAttribute, int> initialPieceMap;

};
