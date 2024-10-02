// Fill out your copyright notice in the Description page of Project Settings.


#include "ConveyorBeltManager.h"
#include "Kismet/GameplayStatics.h"
#include "BaseConveyorBelt.h"
#include "BaseMachine.h"

// Sets default values
AConveyorBeltManager::AConveyorBeltManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AConveyorBeltManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> tempConveyor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseConveyorBelt::StaticClass(), tempConveyor);
	for(AActor* singleActor : tempConveyor)
	{
		if(singleActor)
		{
			ABaseConveyorBelt* singleConveyor = Cast<ABaseConveyorBelt>(singleActor);
			if(singleConveyor) conveyorBelts.Add(singleConveyor);
		}
	}

	TArray<AActor*> tempMachines;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseMachine::StaticClass(), tempMachines);
	for(AActor* singleActor : tempMachines)
	{
		if(singleActor)
		{
			ABaseMachine* singleMachine = Cast<ABaseMachine>(singleActor);
			if(singleMachine)
			{
				singleMachine->conveyorEvent.BindUObject(this, &AConveyorBeltManager::SetStatusForConveyorBelt);
				machines.Add(singleMachine);
			}
		}
	}
	
}

// Called every frame
void AConveyorBeltManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AConveyorBeltManager::SetStatusForConveyorBelt(FName machine, bool status)
{
	for(ABaseConveyorBelt* singleConveyor : conveyorBelts)
	{
		if(singleConveyor->ActorHasTag(machine))
		{
			singleConveyor->SetConveyorBeltPower(status);
		}
	}

}
