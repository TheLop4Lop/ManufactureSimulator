// Fill out your copyright notice in the Description page of Project Settings.


#include "ManagerComputer.h"
#include "Kismet/GameplayStatics.h"
#include "ManagerSupplierWidget.h"
#include "EProductProperties.h"
#include "ProductionScreen.h"
#include "StorageManager.h"
#include "SupplierCost.h"
#include "OrderScreen.h"

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

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOrderScreen::StaticClass(), actorInWorld);
    for(AActor* singleActor : actorInWorld)
    {
        if(singleActor && singleActor->ActorHasTag(upcomingTag))
        {
            upcomingOrderScreen = Cast<AOrderScreen>(singleActor);

        }else if(singleActor && singleActor->ActorHasTag(currentTag))
        {
            currentOrderScreen = Cast<AOrderScreen>(singleActor);

        }else if(singleActor && singleActor->ActorHasTag(lastTag))
        {
            lastOrderScreen = Cast<AOrderScreen>(singleActor);
        }
    }

    GenerateOrdersForTheDay(); // Generates random orders.
    UE_LOG(LogTemp, Display, TEXT("%s"), *gneratedOrders[0].selectionOrder);
    UE_LOG(LogTemp, Display, TEXT("%i"), gneratedOrders[0].orderQuantity);

}

void AManagerComputer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(storageManager && productionScreen)
    {
        productionScreen->SetEarningsGoal(expectedEarnings);
        productionScreen->SetCurrentEarnings(expectedEarnings);
        //storageManager->GetTotalAmountOfProducedProducts()
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
        
        computerWidget->ordersSelectedDelegate.BindUObject(this, &AManagerComputer::StoreSelectedOrders);
        computerWidget->SetOrdersToSelect(gneratedOrders);

        if(ordersByIndex.Num() > 0)
        {
            computerWidget->DisplaySelectedOrdersFromMemory(ordersByIndex);
        }
	}

}

///////////////////////////////////// SUPPLIER PROPERTIES ////////////////////////////////
// Sections for supplier properties. FOR THE MOMENT THIS CLASS ACTS LIKE THE SUPPLIER.

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

///////////////////////////////////// CUSTOMER PROPERTIES ////////////////////////////////
// Sections for customer code petitions properties. FOR THE MOMENT THIS CLASS ACTS LIKE THE COSTUMERS.

// Generates 10 random orders for selection.
void AManagerComputer::GenerateOrdersForTheDay()
{
    for(int i = 0; i < 10; i++)
    {
        int randomIndex = (int)FMath::RandRange(1, 3);
        FString orderToSelect;
        float earnings;

        switch (randomIndex)
        {
        case 1:
            orderToSelect = "M1";
            earnings = (15.0f * sellPercent);
            break;

        case 2:
            orderToSelect = "M2";
            earnings = (20.0f * sellPercent);
            break;

        case 3:
            orderToSelect = "M3";
            earnings = (15.0f * sellPercent);
            break;
        
        default:
            break;
        }
        
        randomIndex = (int)FMath::RandRange(1, 3);
        switch (randomIndex)
        {
        case 1:
            orderToSelect += "S1";
            earnings += (15.0f * sellPercent);
            break;

        case 2:
            orderToSelect += "S2";
            earnings += (20.0f * sellPercent);
            break;

        case 3:
            orderToSelect += "S3";
            earnings += (25.0f * sellPercent);
            break;
        
        default:
            break;
        }

        randomIndex = (int)FMath::RandRange(1, 3);
        switch (randomIndex)
        {
        case 1:
            orderToSelect += "F1";
            earnings += (15.0f * sellPercent);
            break;

        case 2:
            orderToSelect += "F2";
            earnings += (20.0f * sellPercent);
            break;

        case 3:
            orderToSelect += "F3";
            earnings += (25.0f * sellPercent);
            break;
        
        default:
            break;
        }

        randomIndex = (int)FMath::RandRange(1, 3);
        switch (randomIndex)
        {
        case 1:
            orderToSelect += "C1";
            earnings += (15.0f * sellPercent);
            break;

        case 2:
            orderToSelect += "C2";
            earnings += (20.0f * sellPercent);
            break;

        case 3:
            orderToSelect += "C3";
            earnings += (25.0f * sellPercent);
            break;
        
        default:
            break;
        }

        FOrderSelection structOrderToSelect;
        structOrderToSelect.orderQuantity = (int)FMath::RandRange(10, 100);
        structOrderToSelect.selectionOrder = orderToSelect;
        structOrderToSelect.estimatedEarnings = earnings;

        gneratedOrders.Add(structOrderToSelect);
    }

}

// Stores the selected index in computer to hold the ordeds for the day from the Generated Orders.
void AManagerComputer::StoreSelectedOrders(TArray<int> selectedOrders, int expected)
{
    expectedEarnings = expected;

    for(int i = 0; i < selectedOrders.Num(); i ++)
    {
        FString order = FString::FromInt(gneratedOrders[selectedOrders[i]].orderQuantity) + " X " 
                            + gneratedOrders[selectedOrders[i]].selectionOrder;

        ordersByIndex.Add(order);
    }

}
