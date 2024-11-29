// Fill out your copyright notice in the Description page of Project Settings.


#include "ManagerComputer.h"
#include "Kismet/GameplayStatics.h"
#include "ManagerSupplierWidget.h"
#include "ProductionScreen.h"
#include "StorageManager.h"
#include "SupplierCost.h"

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

    if(computerWidget)
    {
        computerWidget->SetValueofCurrentMoney(currentMoney);
    }

}

// Adds widget and assign the player controller to it.
void AManagerComputer::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	characterController = CharacterController;
	computerWidget = Cast<UManagerSupplierWidget>(CreateWidget(characterController, computerClass));

	if(computerWidget)
	{
		computerWidget->AddToViewport();
		computerWidget->confirmEvent.BindUObject(this, &AManagerComputer::ReplenishRawMaterialInStorage);
		computerWidget->exitButtonEvent.BindUObject(this, &ABaseComputer::PublicWidgetBindResetController);
	}

}

// Called to ask for raw material. FOR THE MOMENT THIS CLASS ACTS LIKE THE SUPPLIER.
void AManagerComputer::ReplenishRawMaterialInStorage(FString rawMaterialCode, int quantity)
{
    if(storageManager)
    {
        if(currentMoney >= SupplierCost::CalculateTotalOrderCost(rawMaterialCode, quantity))
        {
            UE_LOG(LogTemp, Display, TEXT("MONEY SPENDED: %f"), SupplierCost::CalculateTotalOrderCost(rawMaterialCode, quantity));
            storageManager->ReplenishRawMaterial(quantity, rawMaterialCode);
            currentMoney -= SupplierCost::CalculateTotalOrderCost(rawMaterialCode, quantity);
            UE_LOG(LogTemp, Display, TEXT("MONEY LEFT: %f"), currentMoney);
        }
        
    }

}
