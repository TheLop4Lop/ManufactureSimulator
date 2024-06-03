// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseComputer.generated.h"

UCLASS()
class MANOFACTURESIMULATOR_API ABaseComputer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseComputer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class TSubclassOf<class UUserWidget> GetComputerWidgetClass();
	void AddWidgetFromComputer(class ACharacterController* CharacterController);

	void SetOrderToStorage();
	void AddToOrdersOfProduct(TArray<FString> Order);
	TArray<FString>& GetStorageOrderHistorial();
	TArray<FString> TemporaryHoldArray;

	bool GetPieceError();

private:
	UPROPERTY(EditAnywhere, Category = "Actor Property", meta = (AllowPrivateAccess))
	UStaticMeshComponent* ComputerMesh;

	UPROPERTY(EditAnywhere, Category = "Storage", meta = (AllowPrivateAccess))
	class ABaseStorage* Storage;

	UPROPERTY(EditAnywhere, Category = "Widgets", meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> ComputerClass;
	class UComputerWidget* ComputerWidget;

	FString CurrentOrder;
	TArray<FString> RawOrders;
	TArray<FString> StorageOrdersCommands;
	TArray<FString> ActualStorageOrders;

	int QuantityPieces;
	FString LengthPiece;
	FString PieceCode;
	bool NoPieceError;

	bool DoOnceCnt;
	bool DoOnce;
	int controlCnt;
	FTimerHandle DelayTimer;

	void OrderToStorage();

	int NewArrayElement;

};
