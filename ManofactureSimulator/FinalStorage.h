// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinalStorage.generated.h"

DECLARE_DELEGATE_OneParam(FOrderInStorage, FString)

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

	FOrderInStorage pieceInStorage;

	// Returns the total amount of product stored.
	int GetTotalOfProductsStored();

private:
	///////////////////////////////////// FINAL STORAGE PROPERTIES ////////////////////////////////
	// Section for Final Storgae Properties.

	// Box to process the final product from production.
	UPROPERTY(EditAnywhere, Category = "Storage Properties", meta = (AllowPrivateAccess))
	class UBoxComponent* storageBox;

	///////////////////////////////////// FINAL STORAGE PROCESS ////////////////////////////////
	// Section for final storage PainterPiece process.

	UPROPERTY(EditAnywhere, Category = "Storage Process", meta = (AllowPrivateAccess))
	int totalProductsStored;

	// Holds the values and quantity of a Finished Piece.
	TMap<FString, int> finishedPiecesCodeInStorage;

};
