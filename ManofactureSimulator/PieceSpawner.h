// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseStorage.h" // To access Enums and Struct
#include "PieceSpawner.generated.h"

UCLASS()
class MANOFACTURESIMULATOR_API APieceSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APieceSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Pawns the Initial Piece product into the world.
	void SpawnInitialPiece(struct FInitialPieceAttribute orderToSpawn);

protected:
	///////////////////////////////////// SPAWNER PROPERTIES ////////////////////////////////
	// Spawner actor properties.

	// Determines the location and rotation when actor spawns.
	class UArrowComponent* arrow;

	///////////////////////////////////// RAW PRODUCT SPAWN ////////////////////////////////
	// Reference to spawn class.

	// Holds a reference to RawProduct template for spawning.
	UPROPERTY(EditAnywhere, Category = "Spawn Product", meta = (AllowPrivateMessage))
	TSubclassOf<class ARawProduct> rawProductClass;

	// Holds different mesh for product.
	UPROPERTY(EditAnywhere, Category = "Spawn Product", meta = (AllowPrivateMessage))
	TArray<UStaticMesh*> productMesh;

	// Holds different FVector values for sizes.
	UPROPERTY(EditAnywhere, Category = "Spawn Product", meta = (AllowPrivateMessage))
	TArray<FVector> productSize;

	// Holds different quality materials for product.
	UPROPERTY(EditAnywhere, Category = "Spawn Product", meta = (AllowPrivateMessage))
	TArray<UMaterial*> qualityMaterial;

};
