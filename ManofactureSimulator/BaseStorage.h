// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseStorage.generated.h"

UENUM(BlueprintType)
enum LengthSizes
{
	L1,
	L2,
	L3,

	NoLength

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

	void SetQuantityOfRawMaterial(int Quantity);
	int GetQuantityOfRawMaterial();

	void SetMasterOrder(int PieceQuantity, FString PieceCode);
	void SetOrderQuantityToSpawn(FString LengthName);
	int GetMasterOrder();

	bool CanProduceOrder(int PieceQuantity, FString LengthName);

	void SetbInOrder(bool OrderStatus);
	bool GetbInOrder();

	int GetMinQuantityOrder();
	int GetMiddleQuantityOrder();
	int GetMaxQuantityOrder();

private:
	UPROPERTY(EditAnywhere, Category = "Actor Properties", meta = (AllowPrivateAccess))
	UStaticMeshComponent* InventoryMesh;

	UPROPERTY(EditAnywhere, Category = "Actor Properties", meta = (AllowPrivateAccess))
	class UBoxComponent* ProductionBox;

	UPROPERTY(EditAnywhere, Category = "Actor Properties", meta = (AllowPrivateAccess))
	UStaticMesh* PieceMesh; //Change it to a static mesh, from UE Reference

	UPROPERTY(EditAnywhere, Category = "Piece", meta = (AllowPrivateAccess))
	TSubclassOf<class APiece> BasicPiece;

	UPROPERTY(EditAnywhere, Category = "Storage Properties", meta = (AllowPrivateAccess))
	int QuantityOfRawMaterial;//Implement logic behind RawMatrial

	FVector SpawnLocation;

	int OrderQuantityToSpawn;
	int QuantityOfOrders;
	FTimerHandle SpawnRest;

	UPROPERTY(EditAnywhere, Category = "Piece Quantity", meta = (AllowPrivateAccess))
	int MinLenghtPiece;

	UPROPERTY(EditAnywhere, Category = "Piece Quantity", meta = (AllowPrivateAccess))
	int MiddleLenghtPiece;

	UPROPERTY(EditAnywhere, Category = "Piece Quantity", meta = (AllowPrivateAccess))
	int MaxLengthPiece;
	int LenghtQuantityOrderPieces;

	class UPieceSpawnProperties* Properties;
	class AInitialPiece* CurrentPiece;

	bool bInOrder;
	bool DoOnce = true;

	bool ShouldSpawnPiece();
	void SpawnOrder();
	bool bOrderDelivered;

	FString ProcessCode;

	LengthSizes ConverStringToEnum(FString ToConvert);

};
