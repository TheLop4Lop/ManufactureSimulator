// Fill out your copyright notice in the Description page of Project Settings.

#include "PieceSpawnProperties.h"
#include <map>
#include <string>
#include "Runtime/Core/Public/Misc/CString.h"

// Sets default values for this component's properties
UPieceSpawnProperties::UPieceSpawnProperties()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}

// Called when the game starts
void UPieceSpawnProperties::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void UPieceSpawnProperties::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UPieceSpawnProperties::SetPieceProperties(int& Index)
{
	switch (Index)
	{
	case 1:
		MaterialIndex = 1;
		TotalTime = TimeMaterialM1 + TimeSizeS1;
		PieceSize = SizeS;
		break;
	case 2:
		MaterialIndex = 2;
		TotalTime = TimeMaterialM1 + TimeSizeS2;
		PieceSize = SizeM;
		break;
	case 3:
		MaterialIndex = 3;
		TotalTime = TimeMaterialM1 + TimeSizeS2;
		PieceSize = SizeL;
		break;

	case 4:
		MaterialIndex = 4;
		TotalTime = TimeMaterialM2 + TimeSizeS1;
		PieceSize = SizeS;
		break;
	case 5:
		MaterialIndex = 5;
		TotalTime = TimeMaterialM2 + TimeSizeS2;
		PieceSize = SizeM;
		break;
	case 6:
		MaterialIndex = 6;
		TotalTime = TimeMaterialM2 + TimeSizeS3;
		PieceSize = SizeL;
		break;

	case 7:
		MaterialIndex = 7;
		TotalTime = TimeMaterialM3 + TimeSizeS1;
		PieceSize = SizeS;
		break;
	case 8:
		MaterialIndex = 8;
		TotalTime = TimeMaterialM3 + TimeSizeS2;
		PieceSize = SizeM;
		break;
	case 9:
		MaterialIndex = 9;
		TotalTime = TimeMaterialM3 + TimeSizeS3;
		PieceSize = SizeL;
		break;
	
	default:
		MaterialIndex = 0;
		TotalTime = 0;
		PieceSize = FVector::ZeroVector;
		break;
	}

}

void UPieceSpawnProperties::SetPiecePropertiesByString(FString Order)
{
	PiecesCodes OrderCode = ConverStringToEnum(Order);

	switch (OrderCode)
	{
	case M1S1:
		MaterialIndex = 1;
		TotalTime = TimeMaterialM1 + TimeSizeS1;
		PieceSize = SizeS;
		break;
	case M1S2:
		MaterialIndex = 2;
		TotalTime = TimeMaterialM1 + TimeSizeS2;
		PieceSize = SizeM;
		break;
	case M1S3:
		MaterialIndex = 3;
		TotalTime = TimeMaterialM1 + TimeSizeS2;
		PieceSize = SizeL;
		break;

	case M2S1:
		MaterialIndex = 4;
		TotalTime = TimeMaterialM2 + TimeSizeS1;
		PieceSize = SizeS;
		break;
	case M2S2:
		MaterialIndex = 5;
		TotalTime = TimeMaterialM2 + TimeSizeS2;
		PieceSize = SizeM;
		break;
	case M2S3:
		MaterialIndex = 6;
		TotalTime = TimeMaterialM2 + TimeSizeS3;
		PieceSize = SizeL;
		break;

	case M3S1:
		MaterialIndex = 7;
		TotalTime = TimeMaterialM3 + TimeSizeS1;
		PieceSize = SizeS;
		break;
	case M3S2:
		MaterialIndex = 8;
		TotalTime = TimeMaterialM3 + TimeSizeS2;
		PieceSize = SizeM;
		break;
	case M3S3:
		MaterialIndex = 9;
		TotalTime = TimeMaterialM3 + TimeSizeS3;
		PieceSize = SizeL;
		break;
	
	default:
		MaterialIndex = 0;
		TotalTime = 0;
		PieceSize = FVector::ZeroVector;
		break;
	}

}

int& UPieceSpawnProperties::GetMaterialIndex()
{
	return MaterialIndex;

}

float& UPieceSpawnProperties::GetTotalTime()
{
	return TotalTime;

}

FVector& UPieceSpawnProperties::GetPieceSize()
{
	return PieceSize;

}

PiecesCodes UPieceSpawnProperties::ConverStringToEnum(FString ToConvert)
{
	std::string Order = std::string(TCHAR_TO_UTF8(*ToConvert));

	static std::map<std::string, PiecesCodes> const table = { 
		{"M1S1",PiecesCodes::M1S1}, {"M1S2",PiecesCodes::M1S2},  {"M1S3",PiecesCodes::M1S3}, 
		{"M2S1",PiecesCodes::M2S1}, {"M2S2",PiecesCodes::M2S2},  {"M2S3",PiecesCodes::M2S3},
		{"M3S1",PiecesCodes::M3S1}, {"M3S2",PiecesCodes::M3S2},  {"M3S3",PiecesCodes::M3S3}};
	
	auto iTable = table.find(Order);
	if (iTable != table.end()) 
	{
  		return iTable->second;
	}

	return PiecesCodes::NoData;

}
