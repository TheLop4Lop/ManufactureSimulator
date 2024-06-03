// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalStorage.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"
#include "Piece.h"

// Sets default values
AFinalStorage::AFinalStorage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InventoryMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Inventory Mesh"));
	InventoryMesh->SetupAttachment(RootComponent);

	BoxEntrance = CreateDefaultSubobject<UBoxComponent>(TEXT("Inventory Entrance"));
	BoxEntrance->SetupAttachment(InventoryMesh);

}

// Called when the game starts or when spawned
void AFinalStorage::BeginPlay()
{
	Super::BeginPlay();

	for(int i = 0; i <= 5; i++)
	{
		CodePiecesToProduce.Add(GenerateCodePieceToProduce());
		UE_LOG(LogTemp, Display, TEXT("Piece: %s"), *CodePiecesToProduce[i]);
	}
	
}

// Called every frame
void AFinalStorage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetEntrancePiece();
	ManageEntrancePiece();

}

FString AFinalStorage::GenerateCodePieceToProduce()
{
	FString RandomPieceCode = "";
	int RandomNumber = GenerateRandomNumber();

	RandomPieceCode = PieceMaterial[RandomNumber];

	RandomNumber = GenerateRandomNumber();
	RandomPieceCode += PieceSize[RandomNumber];

	RandomNumber = GenerateRandomNumber();
	RandomPieceCode += PieceForm[RandomNumber];

	RandomNumber = GenerateRandomNumber();
	RandomPieceCode += PieceColor[RandomNumber];

	return RandomPieceCode;

}

int AFinalStorage::GenerateRandomNumber()
{
	return FMath::RandRange(0, 2);

}

void AFinalStorage::GetEntrancePiece()
{
	BoxEntrance->GetOverlappingActors(ActorsEntrance);
	for(AActor* SinglePiece: ActorsEntrance)
	{
		if(SinglePiece != nullptr)
		{
			Piece = Cast<APiece>(SinglePiece);
		}
	}

}

void AFinalStorage::ManageEntrancePiece()
{
	if(BoxEntrance->IsOverlappingActor(Piece))
	{
		PieceProductionCode = Piece->GetPieceProcessCode();
		Piece->DestroyPiece();

		if(CodePiecesToProduce.Contains(PieceProductionCode))
		{
			cnt++;
			SetAmountOfMoneyByPiece(PieceProductionCode);
		}else
		{
			failCnt++;
			MoneyMade = MoneyMade - (PieceCost/4);
		}
	}

}

void AFinalStorage::SetAmountOfMoneyByPiece(FString PieceCode)
{
	float ExtraBonus = 0;
	if(PieceCode.Contains("M3") || PieceCode.Contains("S3"))
	{
		ExtraBonus += 20.55;
	}else if(PieceCode.Contains("M2") || PieceCode.Contains("S2"))
	{
		ExtraBonus += 10.55;
	}else if(PieceCode.Contains("M1") || PieceCode.Contains("S1"))
	{
		ExtraBonus += 5.55;
	}

	MoneyMade += PieceCost + ExtraBonus;
	UE_LOG(LogTemp, Display, TEXT("Money Made: %f"), MoneyMade);
}
