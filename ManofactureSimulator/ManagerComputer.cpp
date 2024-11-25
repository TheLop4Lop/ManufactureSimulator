// Fill out your copyright notice in the Description page of Project Settings.


#include "ManagerComputer.h"
#include "Kismet/GameplayStatics.h"
#include "ProductionScreen.h"
#include "StorageManager.h"

AManagerComputer::AManagerComputer()
{
    PrimaryActorTick.bCanEverTick = true;

}

void AManagerComputer::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> actorInWorld;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStorageManager::StaticClass(), actorInWorld);
    if(actorInWorld.IsValidIndex(0)) storageManager = Cast<AStorageManager>(actorInWorld[0]);

    actorInWorld.Empty();
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProductionScreen::StaticClass(), actorInWorld);
    if(actorInWorld.IsValidIndex(0)) productionScreen = Cast<AProductionScreen>(actorInWorld[0]);

}

void AManagerComputer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(storageManager && productionScreen)
    {
        productionScreen->SetProductsProduced(storageManager->GetTotalAmountOfProducedProducts());
    }

}
