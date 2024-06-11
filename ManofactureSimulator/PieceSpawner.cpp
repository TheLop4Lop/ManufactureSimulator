// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceSpawner.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "StorageManager.h"
#include "RawProduct.h"

// Sets default values
APieceSpawner::APieceSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	RootComponent = arrow;

}

// Called when the game starts or when spawned
void APieceSpawner::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStorageManager::StaticClass(), actorsInWorld);
	if(actorsInWorld.IsValidIndex(0)) storageManager = Cast<AStorageManager>(actorsInWorld[0]);

	if(storageManager)
	{
		storageManager->orderToProcess.AddDynamic(this, &APieceSpawner::SpawnInitialPiece);
	}

}

// Called every frame
void APieceSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Pawns the Initial Piece product into the world.
void APieceSpawner::SpawnInitialPiece(FInitialPieceAttribute orderToSpawn, int quantity)
{
	ARawProduct* product = GetWorld()->SpawnActor<ARawProduct>(rawProductClass, arrow->GetRelativeLocation(), arrow->GetRelativeRotation());
	
	if(productMesh.Num() > 2 && productSize.Num() > 2 && qualityMaterial.Num() > 2)
	{
		switch (orderToSpawn.Length)
		{
		case EMaterialLength::LENGTH_SHORT:
			
			break;
		case EMaterialLength::LENGTH_MEDIUM:
			product->SetRawProductMesh(productMesh[1]);
			break;
		case EMaterialLength::LENGTH_LARGE:
			product->SetRawProductMesh(productMesh[2]);
			break;
		
		default:
			break;
		}

		switch (orderToSpawn.Size)
		{
		case EMaterialSize::SIZE_SMALL:
			product->SetRawProductSize(productSize[0]);
			break;
		case EMaterialSize::SIZE_MEDIUM:
			product->SetRawProductSize(productSize[1]);
			break;
		case EMaterialSize::SIZE_BIG:
			product->SetRawProductSize(productSize[2]);
			break;

		default:
			break;
		}

		switch (orderToSpawn.Quality)
		{
		case EMaterialQuality::QUALITY_LOW:
			product->SetRawProductMaterial(qualityMaterial[0]);
			break;
		case EMaterialQuality::QUALITY_MEDIUM:
			product->SetRawProductMaterial(qualityMaterial[1]);
			break;
		case EMaterialQuality::QUALITY_HIGH:
			product->SetRawProductMaterial(qualityMaterial[2]);
			break;
		
		default:
			break;
		}
	}

}
