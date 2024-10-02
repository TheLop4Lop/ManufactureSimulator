// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConveyorBeltManager.generated.h"

UCLASS()
class MANOFACTURESIMULATOR_API AConveyorBeltManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConveyorBeltManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	///////////////////////////////////// CONVEYOR ////////////////////////////////
	// Section for all actions for conveyor belts in the map.

	// Holds referenct to all Conveyor Belt actors in the map.
	TArray<class ABaseConveyorBelt*> conveyorBelts;

	void SetStatusForConveyorBelt(FName machine, bool status);

	///////////////////////////////////// MACHINES ////////////////////////////////
	// Section for all actions of BaseMachine class actors in the map.

	// Holds reference to all BaseMachine actors in the map.
	TArray<class ABaseMachine*> machines;

};
