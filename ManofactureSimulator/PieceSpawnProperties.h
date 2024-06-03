// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PieceSpawnProperties.generated.h"

UENUM(BlueprintType)
enum PiecesCodes
{
	M1S1,
	M1S2,
	M1S3,

	M2S1,
	M2S2,
	M2S3,

	M3S1,
	M3S2,
	M3S3,

	NoData
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MANOFACTURESIMULATOR_API UPieceSpawnProperties : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPieceSpawnProperties();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetPieceProperties(int& Index);
	void SetPiecePropertiesByString(FString Order);

	int& GetMaterialIndex();
	float& GetTotalTime();
	FVector& GetPieceSize();

private:
	//UPROPERTY - Process Property
	UPROPERTY(EditAnywhere, Category = "Process Property", meta = (AllowPrivateAccess))
	TEnumAsByte<PiecesCodes> PieceCode;

	//UPROPERTY - Time by Piece Code; Material
	UPROPERTY(EditAnywhere, Category = "Time By Material", meta = (AllowPrivateAccess))
	float TimeMaterialM1 = 1.f;

	UPROPERTY(EditAnywhere, Category = "Time By Material", meta = (AllowPrivateAccess))
	float TimeMaterialM2 = 3.f;

	UPROPERTY(EditAnywhere, Category = "Time By Material", meta = (AllowPrivateAccess))
	float TimeMaterialM3 = 5.f;

	//UPROPERTY - Time by Piece Code; Size
	UPROPERTY(EditAnywhere, Category = "Time By Size", meta = (AllowPrivateAccess))
	float TimeSizeS1 = 1.f;

	UPROPERTY(EditAnywhere, Category = "Time By Size", meta = (AllowPrivateAccess))
	float TimeSizeS2 = 2.f;

	UPROPERTY(EditAnywhere, Category = "Time By Size", meta = (AllowPrivateAccess))
	float TimeSizeS3 = 3.f;

	//UPROPERTY - Piece Size
	UPROPERTY(EditAnywhere, Category = "Sizes", meta = (AllowPrivateAccess))
	FVector SizeS = FVector(0.4f);

	UPROPERTY(EditAnywhere, Category = "Sizes", meta = (AllowPrivateAccess))
	FVector SizeM = FVector(0.5f);

	UPROPERTY(EditAnywhere, Category = "Sizes", meta = (AllowPrivateAccess))
	FVector SizeL = FVector(0.7f);

	int MaterialIndex;
	float TotalTime;
	FVector PieceSize;

	PiecesCodes ConverStringToEnum(FString ToConvert);

};
