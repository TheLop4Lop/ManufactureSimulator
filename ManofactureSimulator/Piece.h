// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Piece.generated.h"

UCLASS()
class MANOFACTURESIMULATOR_API APiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetPieceBasicProperties(int& Index, float& Time);
	void SetPieceMeshProperties(UStaticMesh* NewMesh, FVector &NewSize);
	void SetPieceMeshMaterialColor(UMaterial* NewMaterial);

	int GetPieceCodeIndex();
	float GetProductionTime();
	FVector GetSize();
	UStaticMesh* GetPieceMesh();
	UMaterial* GetPieceMaterial();

	void SetPieceProcessCode(FString ProcessCode);
	FString GetPieceProcessCode();

	void DestroyPiece();

protected:
	//UPROPERTY - Actor Property
	UPROPERTY(EditAnywhere, Category = "Actor Property", meta = (AllowPrivateAccess))
	UStaticMeshComponent* PieceMesh;

	//Code index, Process Time & Size
	int MaterialIndex;
	float TotalTime;	
	FVector PieceSize;

	FString PieceProcessCode;
	
};
