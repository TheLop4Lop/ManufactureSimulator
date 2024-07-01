// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceSpawner.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
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

}

// Called every frame
void APieceSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Pawns the Initial Piece product into the world.
void APieceSpawner::SpawnInitialPiece(FInitialPieceAttribute orderToSpawn)
{
	productCode = "";
	UStaticMesh* selectedMesh = nullptr;
	UMaterial* selectedMaterial = nullptr;
	FVector selectesSize = FVector::ZeroVector;

	if(productMesh.Num() > 2 && productSize.Num() > 2 && qualityMaterial.Num() > 2)
	{
		switch (orderToSpawn.Quality)
		{
		case EMaterialQuality::QUALITY_LOW:
			selectedMaterial = qualityMaterial[0];
			productCode += "M1";
			break;
		case EMaterialQuality::QUALITY_MEDIUM:
			selectedMaterial = qualityMaterial[1];
			productCode += "M2";
			break;
		case EMaterialQuality::QUALITY_HIGH:
			selectedMaterial = qualityMaterial[3];
			productCode += "M3";
			break;
		
		default:
			break;
		}

		switch (orderToSpawn.Size)
		{
		case EMaterialSize::SIZE_SMALL:
			selectesSize = productSize[0];
			productCode += "S1";
			break;
		case EMaterialSize::SIZE_MEDIUM:
			selectesSize = productSize[1];
			productCode += "S2";
			break;
		case EMaterialSize::SIZE_BIG:
			selectesSize = productSize[2];
			productCode += "S3";
			break;

		default:
			break;
		}

		switch (orderToSpawn.Length)
		{
		case EMaterialLength::LENGTH_SHORT:
			selectedMesh = productMesh[0];
			productCode += "L1";
			break;
		case EMaterialLength::LENGTH_MEDIUM:
			selectedMesh = productMesh[1];
			productCode += "L2";
			break;
		case EMaterialLength::LENGTH_LARGE:
			selectedMesh = productMesh[2];
			productCode += "L3";
			break;
		
		default:
			break;
		}
	}

	ARawProduct* product = GetWorld()->SpawnActor<ARawProduct>(rawProductClass, arrow->GetRelativeLocation(), arrow->GetRelativeRotation());
	if(product && selectedMesh && selectedMaterial)
	{
		product->SetProductCode(productCode);
		product->SetsProductProperties(selectedMesh, selectedMaterial, selectesSize);
	}

}
