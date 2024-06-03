// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseStorage.h"
#include <map>
#include <string>
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PieceSpawnProperties.h"
#include "InitialPiece.h"

#define MaxOrder 10
#define MiddleOrder 5
#define MinOrder 2
#define NullOrder 0

// Sets default values
ABaseStorage::ABaseStorage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InventoryMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Inventory Mesh"));
	InventoryMesh->SetupAttachment(RootComponent);

	ProductionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Spawn"));
	ProductionBox->SetupAttachment(InventoryMesh);

}

// Called when the game starts or when spawned
void ABaseStorage::BeginPlay()
{
	Super::BeginPlay();

	Properties = FindComponentByClass<UPieceSpawnProperties>();
	
	FVector TemporaryVector = ProductionBox->GetRelativeLocation();
	FTransform ComponentTransform = ProductionBox->GetOwner()->GetTransform();
	FVector WorldLocation = ComponentTransform.TransformPosition(TemporaryVector);

	SpawnLocation = WorldLocation;

	UE_LOG(LogTemp, Display, TEXT("BEGIN - L1: %i, L2: %%i, L3: %i"), MinLenghtPiece, MiddleLenghtPiece, MaxLengthPiece);

}

// Called every frame
void ABaseStorage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bInOrder && DoOnce)
	{
		SpawnOrder();
	}
	
}

bool ABaseStorage::CanProduceOrder(int PieceQuantity, FString LengthName)
{
	LengthSizes LengthOrder = ConverStringToEnum(LengthName);
	int CurrentQuantityOfPiece;

	switch (LengthOrder)
	{
	case L1:
			CurrentQuantityOfPiece = MinLenghtPiece;
		break;

	case L2:
			CurrentQuantityOfPiece = MiddleLenghtPiece;
		break;

	case L3:
			CurrentQuantityOfPiece = MaxLengthPiece;
		break;

	default:
		CurrentQuantityOfPiece = 0;
		break;
	}

	if(CurrentQuantityOfPiece - PieceQuantity < 0)
	{
		return false;
	}

	LenghtQuantityOrderPieces = PieceQuantity;
	UE_LOG(LogTemp, Display, TEXT("LenghtQuantityOrderPieces: %i"), LenghtQuantityOrderPieces);
	return true;
}

void ABaseStorage::SetbInOrder (bool OrderStatus)
{
	bInOrder = OrderStatus;

}

void ABaseStorage::SetMasterOrder(int PieceQuantity, FString PieceCode)
{
	if(Properties != nullptr)
	{
		ProcessCode = PieceCode;
		QuantityOfOrders = PieceQuantity;
		Properties->SetPiecePropertiesByString(PieceCode);
		bInOrder = true;
	}

}

bool ABaseStorage::GetbInOrder()
{
	return bInOrder;
	
}

void ABaseStorage::SetOrderQuantityToSpawn(FString LengthName)
{
	LengthSizes LengthOrder = ConverStringToEnum(LengthName);

	switch (LengthOrder)
	{
	case L1:
			OrderQuantityToSpawn = MinOrder;
			MinLenghtPiece -= LenghtQuantityOrderPieces;
			UE_LOG(LogTemp, Display, TEXT("MinLenghtPiece: %i"), MinLenghtPiece);
		break;

	case L2:
			OrderQuantityToSpawn = MiddleOrder;
			MiddleLenghtPiece -= LenghtQuantityOrderPieces;
		break;

	case L3:
			OrderQuantityToSpawn = MaxOrder;
			MaxLengthPiece -= LenghtQuantityOrderPieces;
			UE_LOG(LogTemp, Display, TEXT("MaxLengthPiece: %i"), MaxLengthPiece);
		break;

	default:
		OrderQuantityToSpawn = NullOrder;
		break;
	}

}

bool ABaseStorage::ShouldSpawnPiece()
{
	APiece* OverlapingPiece = nullptr;
	TArray<AActor*> ActorsExit;
	ProductionBox->GetOverlappingActors(ActorsExit);
	for(AActor* SinglePiece : ActorsExit)
	{
		if(SinglePiece != nullptr)
		{
			OverlapingPiece = Cast<APiece>(SinglePiece);
		}
	}

	if(ProductionBox->IsOverlappingActor(OverlapingPiece))
	{
		return false;
	}

	return true;

}

void ABaseStorage::SpawnOrder()
{
	UClass* ClassToSpawn = nullptr;
	FRotator ZeroRot = FRotator::ZeroRotator;
	if(BasicPiece != nullptr)
	{
		ClassToSpawn = BasicPiece;
	}
	
	if(Properties != nullptr)
	{
		if(ClassToSpawn != nullptr && PieceMesh != nullptr && ShouldSpawnPiece())//Change it to a static mesh, from UE Reference
		{
			CurrentPiece = GetWorld()->SpawnActor<AInitialPiece>(ClassToSpawn, SpawnLocation, ZeroRot);
			CurrentPiece->SetPieceBasicProperties(Properties->GetMaterialIndex(), Properties->GetTotalTime());
			CurrentPiece->SetPieceMeshProperties(PieceMesh, Properties->GetPieceSize());
			CurrentPiece->SetQuantityProduction(OrderQuantityToSpawn);
			CurrentPiece->SetPieceProcessCode(ProcessCode);

			QuantityOfOrders--;
			GetWorldTimerManager().SetTimer(SpawnRest, 5.f, false);
			if(QuantityOfOrders == 0)
			{
				bInOrder = false;
			}
		}
	}

}

void ABaseStorage::SetQuantityOfRawMaterial(int Quantity)
{
	QuantityOfRawMaterial += Quantity;

}

int ABaseStorage::GetQuantityOfRawMaterial()
{
	return QuantityOfRawMaterial;

}

LengthSizes ABaseStorage::ConverStringToEnum(FString ToConvert)
{
	std::string Order = std::string(TCHAR_TO_UTF8(*ToConvert));

	static std::map<std::string, LengthSizes> const table = { 
		{"L1",LengthSizes::L1}, {"L2",LengthSizes::L2},  {"L3",LengthSizes::L3}};
	
	auto iTable = table.find(Order);
	if (iTable != table.end()) 
	{
  		return iTable->second;
	}

	return LengthSizes::NoLength;

}

int ABaseStorage::GetMinQuantityOrder()
{
	return MinLenghtPiece;

}

int ABaseStorage::GetMiddleQuantityOrder()
{
	return MiddleLenghtPiece;

}

int ABaseStorage::GetMaxQuantityOrder()
{
	return MaxLengthPiece;

}

