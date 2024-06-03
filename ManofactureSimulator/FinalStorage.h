// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinalStorage.generated.h"

UCLASS()
class MANOFACTURESIMULATOR_API AFinalStorage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFinalStorage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Actor Properties", meta = (AllowPrivateAccess))
	UStaticMeshComponent* InventoryMesh;

	UPROPERTY(EditAnywhere, Category = "Actor Properties", meta = (AllowPrivateAccess))
	class UBoxComponent* BoxEntrance;

	UPROPERTY(EditAnywhere, Category = "Piece", meta = (AllowPrivateAccess))
	TSubclassOf<class APiece> FinalPiece;

private:
	void GetEntrancePiece();
	void ManageEntrancePiece();
	TArray<AActor*> ActorsEntrance;
	class APiece* Piece;

	FString PieceProductionCode;

	UPROPERTY(EditAnywhere, Category = "TESTING", meta = (AllowPrivateAccess))
	int cnt;
	UPROPERTY(EditAnywhere, Category = "TESTING", meta = (AllowPrivateAccess))
	int failCnt;

	TArray<FString> PieceMaterial = {TEXT("M1"), TEXT("M2"), TEXT("M3")};
	TArray<FString> PieceSize = {TEXT("S1"), TEXT("S2"), TEXT("S3")};
	TArray<FString> PieceForm = {TEXT("F1"), TEXT("F2"), TEXT("F3")};
	TArray<FString> PieceColor = {TEXT("C1"), TEXT("C2"), TEXT("C3")};

	FString GenerateCodePieceToProduce();
	int GenerateRandomNumber();
	TArray<FString> CodePiecesToProduce;
	TArray<int> PieceCounters = {0, 0, 0, 0, 0};

	void SetAmountOfMoneyByPiece(FString PieceCode);

	UPROPERTY(EditAnywhere, Category = "TESTING", meta = (AllowPrivateAccess))
	float MoneyMade;

	UPROPERTY(EditAnywhere, Category = "TESTING", meta = (AllowPrivateAccess))
	float PieceCost = 50.00;

};
