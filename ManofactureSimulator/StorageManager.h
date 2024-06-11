// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseStorage.h" // To access Enums and Struct
#include "StorageManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOrderProcessed, FInitialPieceAttribute, ProductID, int, Quantity);

UCLASS()
class MANOFACTURESIMULATOR_API AStorageManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStorageManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Delegate event to Spawn order.
	FOnOrderProcessed orderToProcess;

	// Recieve a FString to convert into Enum. Returns False if not enough material or returns true othewise and trigger event for spawn product.
	bool CanProduceProductOrder(FString Order, int quantity);

protected:
	///////////////////////////////////// STORAGE REFERENCES ////////////////////////////////
	// Section for Storages references

	// Reference in world of Base Storage, responsable of holding raw material for production.
	class ABaseStorage* baseStorage;
	// Reference in world of Final Storage, responsable of holding produced materials by producton.
	class AFinalStorage* finalStorage;

	///////////////////////////////////// CONVERT TO ENUMS ////////////////////////////////
	// Methods for convert FString to enum.

	// Retrieves a string and convert it into a EMaterialQuality enum.
	EMaterialQuality ConverStringToEnumQuality(FString quality);

	// Retrieves a string and convert it into a EMaterialSize enum.
	EMaterialSize ConverStringToEnumSize(FString quality);

	// Retrieves a string and convert it into a EMaterialLength enum.
	EMaterialLength ConverStringToEnumLength(FString quality);

};
