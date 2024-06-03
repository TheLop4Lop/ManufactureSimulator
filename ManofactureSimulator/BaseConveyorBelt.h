// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseConveyorBelt.generated.h"

UCLASS()
class MANOFACTURESIMULATOR_API ABaseConveyorBelt : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseConveyorBelt();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetConveyorBeltPower(bool bEnergy);
	void SetConveyorBeltSpeed(float NewFinalSpeed);

	bool IsPiecesInConveyor();

protected:
	UPROPERTY(EditAnywhere, Category = "Actor Property", meta = (AllowPrivateAccess))
	UStaticMeshComponent* BeltMesh;

	UPROPERTY(EditAnywhere, Category = "Actor Property", meta = (AllowPrivateAccess))
	class UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere, Category = "Actor Property", meta = (AllowPrivateAccess))
	class UBoxComponent* ConveyorBox;

	UPROPERTY(EditAnywhere, Category = "Belt Property", meta = (AllowPrivateAccess))
	float Speed;
	
	UPROPERTY(EditAnywhere, Category = "Belt Property", meta = (AllowPrivateAccess))
	bool bPower;

	UPROPERTY(EditAnywhere, Category = "Maintenance Property", meta = (AllowPrivateAccess))
	bool bInMaintenance;

	UPROPERTY(EditAnywhere, Category = "Maintenance Property", meta = (AllowPrivateAccess))
	float MaintenanceTime;

	class ABaseMachinery* MachineOwner;

	TArray<AActor*> Actors;

	FTimerHandle MaintenanceTimer;
	virtual void HandleMaintenanceMode();
	bool DoOnce = true;

	FTimerHandle ConveyorTimer;
	void ManageConveyorTimer();
	bool bVelocityIncrease;

	bool bShouldConveyorLoop;
	bool bPiecesInCoveyor;

};
