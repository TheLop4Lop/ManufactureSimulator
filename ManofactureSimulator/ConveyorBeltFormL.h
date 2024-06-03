// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseConveyorBelt.h"
#include "ConveyorBeltFormL.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API AConveyorBeltFormL : public ABaseConveyorBelt
{
	GENERATED_BODY()

public:
	AConveyorBeltFormL();

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Actor Property", meta = (AllowPrivateAccess))
	class UArrowComponent* ArrowL;

	UPROPERTY(EditAnywhere, Category = "Actor Property", meta = (AllowPrivateAccess))
	class UBoxComponent* ConveyorBoxL;

	TArray<AActor*> ActorsL;
	TArray<AActor*> TotalActors;

	virtual void HandleMaintenanceMode() override;
	
};
