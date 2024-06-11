// Fill out your copyright notice in the Description page of Project Settings.

#include "StorageManager.h"
#include "Runtime/Core/Public/Misc/CString.h"
#include "Kismet/GameplayStatics.h"
#include "FinalStorage.h"
#include "BaseStorage.h"

#include <map>
#include <string>

// Singleton - Static method that returns a single QualityMap instance.
static const std::map<std::string, EMaterialQuality>& GetQualityMap()
{
	static const std::map<std::string, EMaterialQuality> tableQuality = { 
		{"M1", EMaterialQuality::QUALITY_LOW}, 
		{"M2", EMaterialQuality::QUALITY_MEDIUM},  
		{"M3", EMaterialQuality::QUALITY_HIGH}};

	return tableQuality;

}

// Singleton - Static method that returns a single GetSizeMap instance.
static const std::map<std::string, EMaterialSize>& GetSizeMap()
{
	static const std::map<std::string, EMaterialSize> tableSize = { 
		{"S1",EMaterialSize::SIZE_SMALL},
		{"S2",EMaterialSize::SIZE_MEDIUM},
		{"S3",EMaterialSize::SIZE_BIG}};

	return tableSize;
}

// Singleton - Static method that returns a single GetLengthMap instance.
static const std::map<std::string, EMaterialLength>& GetLengthMap()
{
	static const std::map<std::string, EMaterialLength> tableLength = { 
		{"L1",EMaterialLength::LENGTH_SHORT},
		{"L2",EMaterialLength::LENGTH_MEDIUM},
		{"L3",EMaterialLength::LENGTH_LARGE}};

	return tableLength;
}

// Sets default values
AStorageManager::AStorageManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStorageManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseStorage::StaticClass(), actorsInWorld);
	if(actorsInWorld.IsValidIndex(0)) baseStorage = Cast<ABaseStorage>(actorsInWorld[0]);

	actorsInWorld.Empty();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFinalStorage::StaticClass(), actorsInWorld);
	if(actorsInWorld.IsValidIndex(0)) finalStorage = Cast<AFinalStorage>(actorsInWorld[0]);

}

// Called every frame
void AStorageManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Recieve a FString to convert into Enum. Returns False if not enough material or returns true othewise and trigger event for spawn product.
bool AStorageManager::CanProduceProductOrder(FString Order, int quantity)
{
	FInitialPieceAttribute productToOrder;

	productToOrder.Quality = ConverStringToEnumQuality(Order.Left(2));
	productToOrder.Size = ConverStringToEnumSize(Order.Mid(2,2));
	productToOrder.Length = ConverStringToEnumLength(Order.Right(2));

	if(baseStorage->OrderIsInInventory(productToOrder, quantity))
	{
		UE_LOG(LogTemp, Display, TEXT("ENOUGH FOR PRODUCT!"));
		orderToProcess.Broadcast(productToOrder, quantity);
		return true;
	}
	UE_LOG(LogTemp, Display, TEXT("NOT ENOUGH FOR PRODUCT!"));
	return false;

}

// Retrieves a string and convert it into a EMaterialQuality enum.
EMaterialQuality AStorageManager::ConverStringToEnumQuality(FString quality)
{
	std::string order = std::string(TCHAR_TO_UTF8(*quality));
	auto& tableQuality = GetQualityMap();
	auto iTable = tableQuality.find(order);
	
	return (iTable != tableQuality.end()) ? iTable->second : EMaterialQuality::QUALITY_LOW;

}

// Retrieves a string and convert it into a EMaterialSize enum.
EMaterialSize AStorageManager::ConverStringToEnumSize(FString size)
{
	std::string order = std::string(TCHAR_TO_UTF8(*size));
	auto& tableSize = GetSizeMap();
	auto iTable = tableSize.find(order);
	
	return (iTable != tableSize.end()) ? iTable->second : EMaterialSize::SIZE_SMALL;

}

// Retrieves a string and convert it into a EMaterialLength enum.
EMaterialLength AStorageManager::ConverStringToEnumLength(FString length)
{
	std::string order = std::string(TCHAR_TO_UTF8(*length));
	auto& tableLength = GetLengthMap();
	auto iTable = tableLength.find(order);
	
	return (iTable != tableLength.end()) ? iTable->second : EMaterialLength::LENGTH_SHORT;

}
