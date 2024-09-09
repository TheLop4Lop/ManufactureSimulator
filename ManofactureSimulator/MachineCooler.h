// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MachineCooler.generated.h"

UCLASS()
class MANOFACTURESIMULATOR_API AMachineCooler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMachineCooler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	///////////////////////////////////// MACHINE PROPERTIES ////////////////////////////////
	// Section for all the machine initial properties.

	// Mesh component for cooler machine
	UPROPERTY(EditAnywhere, Category = "Machine Properties", meta = (AllowPrivateAccess))
	UStaticMeshComponent* machineMesh;

	// Box Component for piece interaction
	UPROPERTY(EditAnywhere, Category = "Machine Properties", meta = (AllowPrivateAccess))
	class UBoxComponent* boxComponent;

	///////////////////////////////////// PRODUCTION PROPERTIES ////////////////////////////////
	// Section for changing piece status on production.

	void CheckProductOverlap();

};
