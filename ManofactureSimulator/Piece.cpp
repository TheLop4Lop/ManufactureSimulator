// Fill out your copyright notice in the Description page of Project Settings.

#include "Piece.h"
#include "Components/CapsuleComponent.h"
#include "Engine/CollisionProfile.h"

// Sets default values
APiece::APiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PieceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Piece Mesh"));
	SetRootComponent(PieceMesh);

}

// Called when the game starts or when spawned
void APiece::BeginPlay()
{
	Super::BeginPlay();
	
	PieceMesh->SetSimulatePhysics(true);
	PieceMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);

	PieceProcessCode = "";
	
}

// Called every frame
void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APiece::SetPieceBasicProperties(int& Index, float& Time)
{
	MaterialIndex = Index;
	TotalTime = Time;

}

void APiece::SetPieceMeshProperties(UStaticMesh* NewMesh, FVector &NewSize)
{
	PieceMesh->SetStaticMesh(NewMesh);
	PieceMesh->SetWorldScale3D(NewSize);

}

void APiece::SetPieceMeshMaterialColor(UMaterial* NewMaterial)
{
	PieceMesh->SetMaterial(0, NewMaterial);

}

UStaticMesh* APiece::GetPieceMesh()
{
	return PieceMesh->GetStaticMesh();

}

UMaterial* APiece::GetPieceMaterial()
{
	return PieceMesh->GetMaterial(0)->GetMaterial();

}

int APiece::GetPieceCodeIndex()
{
	return MaterialIndex;

}

FVector APiece::GetSize()
{
	return PieceSize;

}

float APiece::GetProductionTime()
{
	return TotalTime;

}

void APiece::DestroyPiece()
{
	Destroy();

}

void APiece::SetPieceProcessCode(FString ProcessCode)
{
	PieceProcessCode += ProcessCode;
	UE_LOG(LogTemp, Display, TEXT("CODE: %s"), *PieceProcessCode);

}

FString APiece::GetPieceProcessCode()
{
	return PieceProcessCode;

}