// Fill out your copyright notice in the Description page of Project Settings.


#include "ManagerComputer.h"
#include "Kismet/GameplayStatics.h"
#include "ManagerSupplierWidget.h"
#include "EProductProperties.h"
#include "ProductionScreen.h"
#include "RefuelerComputer.h"
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

    if(storageManager)
    {
        storageManager->orderStored.BindUObject(this, &AManagerComputer::UpdateCurrentEarnings);
        storageManager->statusOnStock.BindUObject(this, &AManagerComputer::UpdateOrdersDataOnStock);
    }

    actorInWorld.Empty();
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProductionScreen::StaticClass(), actorInWorld);
    if(actorInWorld.IsValidIndex(0)) productionScreen = Cast<AProductionScreen>(actorInWorld[0]);

    actorInWorld.Empty();
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARefuelerComputer::StaticClass(), actorInWorld);
    if(actorInWorld.IsValidIndex(0))
    {
        refuelerComputer = Cast<ARefuelerComputer>(actorInWorld[0]);
        if(refuelerComputer)
        {
            UE_LOG(LogTemp, Display, TEXT("REFUELER COMPUTER FOUND!"));
            refuelerComputer->oilCostAmount.BindUObject(this, &AManagerComputer::CalculateOilTransaction);
            refuelerComputer->lubricantCostAmount.BindUObject(this, &AManagerComputer::CalculateLubricantTransaction);
        }
    }

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOrderScreen::StaticClass(), actorInWorld);
    for(AActor* singleActor : actorInWorld)
    {
        if(singleActor && singleActor->ActorHasTag(currentTag))
        {
            currentOrderScreen = Cast<AOrderScreen>(singleActor);

        }else if(singleActor && singleActor->ActorHasTag(lastTag))
        {
            lastOrderScreen = Cast<AOrderScreen>(singleActor);
        }
    }

    GenerateOrdersForTheDay(); // Generates random orders.
    initialMoney = currentEarnings;

}

void AManagerComputer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(storageManager && productionScreen)
    {
        productionScreen->SetEarningsGoal(expectedEarnings);
        productionScreen->SetCurrentEarnings(currentEarnings);
    }

    if(computerWidget)
    {
        computerWidget->SetValueofCurrentMoney(currentMoney);
    }
    currentMoneyStatus.ExecuteIfBound(currentMoney); // Initilices the money for player display.

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
        
        computerWidget->askNewOrders.BindUObject(this, &AManagerComputer::RegenerateTheOrdersToSelect);
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

///////////////////////////////////// PRODUCTION COST PROPERTIES ////////////////////////////////
// Section for the piece production cost and product final cost.

// Calculates the value of material by FString.
float AManagerComputer::CalculateMaterialProductionCostByString(FString materialCode)
{
    float materialCost = 0.0f;
    switch (UEProductProperties::ConverStringToEnumQuality(materialCode))
    {
    case EPieceMaterial::QUALITY_LOW:
        materialCost = (lowQualityCost * sellPercent);
        break;
    
    case EPieceMaterial::QUALITY_MEDIUM:
        materialCost = (lowQualityCost * sellPercent);
        break;

    case EPieceMaterial::QUALITY_HIGH:
        materialCost = (lowQualityCost * sellPercent);
        break;

    default:
        break;
    }

    return materialCost;

}

// Calculates the value of size by FString.
float AManagerComputer::CalculateSizeProductionCostByString(FString sizeCode)
{
    float sizeCost = 0.0f;
    switch (UEProductProperties::ConverStringToEnumSize(sizeCode))
    {
    case EPieceSize::SIZE_SMALL:
        sizeCost = (smallSizeCost * sellPercent);
        break;
    
    case EPieceSize::SIZE_MEDIUM:
        sizeCost = (middSizeCost * sellPercent);
        break;

    case EPieceSize::SIZE_BIG:
        sizeCost = (bigSizeCost * sellPercent);
        break;

    default:
        break;
    }

    return sizeCost;
    
}

// Calculates the value of shape by FString.
float AManagerComputer::CalculateFormProductionCostByString(FString formCode)
{
    float shapeCost = 0.0f;
    switch (UEProductProperties::ConverStringToEnumForm(formCode))
    {
    case EPieceForm::FORM_CONE:
        shapeCost = (f1Cost * sellPercent);
        break;
    
    case EPieceForm::FORM_CYLINDER:
        shapeCost = (f2Cost * sellPercent);
        break;

    case EPieceForm::FORM_TORUS:
        shapeCost = (f3Cost * sellPercent);
        break;

    default:
        break;
    }

    return shapeCost;
    
}

// Calculates the value of color by FString.
float AManagerComputer::CalculateColorProductionCostByString(FString colorCode)
{
    float colorCost = 0.0f;
    switch (UEProductProperties::ConverStringToEnumColor(colorCode))
    {
    case EPieceColor::COLOR_BLUE:
        colorCost = (c1Cost * sellPercent);
        break;
    
    case EPieceColor::COLOR_RED:
        colorCost = (c2Cost * sellPercent);
        break;

    case EPieceColor::COLOR_GREEN:
        colorCost = (c3Cost * sellPercent);
        break;

    default:
        break;
    }

    return colorCost;
    
}

// Updates the current earnings produced to dislay,
void AManagerComputer::UpdateCurrentEarnings(FString productCode, bool isOnOotD) ////////////////////////////////
{
    if(isOnOotD)
    {
        UpdateOrderProductionStatusOnScreen(productCode);

        currentEarnings += (int)(CalculateMaterialProductionCostByString(productCode.Left(2)) + CalculateSizeProductionCostByString(productCode.Mid(2, 2)) + 
                                CalculateFormProductionCostByString(productCode.Mid(4, 2)) + CalculateColorProductionCostByString(productCode.Right(2)));

        currentMoney += (float)currentEarnings;
        currentMoneyStatus.ExecuteIfBound(currentMoney);
    }else
    {
        lossMoney += (int)(CalculateMaterialProductionCostByString(productCode.Left(2)) + CalculateSizeProductionCostByString(productCode.Mid(2, 2)) + 
                                CalculateFormProductionCostByString(productCode.Mid(4, 2)) + CalculateColorProductionCostByString(productCode.Right(2)));
    }
    
}

// Updates the data on Stock.
void AManagerComputer::UpdateOrdersDataOnStock(TArray<FOrderInfo> updatedStockStatus)
{
    TArray<FOrderOTD> ordersStatus;
    ordersStatus.Empty();
    for(int i = 0 ; i < updatedStockStatus.Num(); i++)
    {
        FOrderOTD singleOrder;
        switch (updatedStockStatus[i].orderStatusInfoEnum)
        {
        case EStorageProductionStatus::CAN_PRODUCE:
            singleOrder.orderColorStatus = FColor::FromHex("094A0BFF"); // Green color, selected from UEditor.
            break;
        
        case EStorageProductionStatus::CANNOT_PRODUCE:
            singleOrder.orderColorStatus = FColor::FromHex("716E03FF"); // Yellow color, selected from UEditor.
            break;

        case EStorageProductionStatus::NO_PRODUCT_STOCKED:
            singleOrder.orderColorStatus = FColor::FromHex("63110DFF"); // Red color, selected from UEditor.
            break;

        default:
            break;
        }

        singleOrder.lxProperties[0] = updatedStockStatus[i].orderLenghtsInfo.l1Quantity;
        singleOrder.lxProperties[1] = updatedStockStatus[i].orderLenghtsInfo.l2Quantity;
        singleOrder.lxProperties[2] = updatedStockStatus[i].orderLenghtsInfo.l3Quantity;

        singleOrder.canProduceByStock = updatedStockStatus[i].totalAmountOfPieceFromStock;

        ordersStatus.Add(singleOrder);
    }
    ordersForMonitor.ExecuteIfBound(ordersByIndex, ordersStatus);

}

///////////////////////////////////// CUSTOMER PROPERTIES ////////////////////////////////
// Sections for customer code petitions properties. FOR THE MOMENT THIS CLASS ACTS LIKE THE COSTUMERS.

// Generates 10 random orders for selection.
void AManagerComputer::GenerateOrdersForTheDay()
{
    gneratedOrders.Empty();
    
    for(int i = 0; i < 10; i++)
    {
        int randomIndex = (int)FMath::RandRange(1, 3);
        FString orderToSelect;
        float earnings = 0.0f;

        switch (randomIndex)
        {
        case 1:
            orderToSelect = "M1";
            earnings = (lowQualityCost * sellPercent);
            break;

        case 2:
            orderToSelect = "M2";
            earnings = (middQualityCost * sellPercent);
            break;

        case 3:
            orderToSelect = "M3";
            earnings = (highQualityCost * sellPercent);
            break;
        
        default:
            break;
        }
        
        randomIndex = (int)FMath::RandRange(1, 3);
        switch (randomIndex)
        {
        case 1:
            orderToSelect += "S1";
            earnings += (smallSizeCost * sellPercent);
            break;

        case 2:
            orderToSelect += "S2";
            earnings += (middSizeCost * sellPercent);
            break;

        case 3:
            orderToSelect += "S3";
            earnings += (bigSizeCost * sellPercent);
            break;
        
        default:
            break;
        }

        randomIndex = (int)FMath::RandRange(1, 3);
        switch (randomIndex)
        {
        case 1:
            orderToSelect += "F1";
            earnings += (f1Cost * sellPercent);
            break;

        case 2:
            orderToSelect += "F2";
            earnings += (f2Cost * sellPercent);
            break;

        case 3:
            orderToSelect += "F3";
            earnings += (f3Cost * sellPercent);
            break;
        
        default:
            break;
        }

        randomIndex = (int)FMath::RandRange(1, 3);
        switch (randomIndex)
        {
        case 1:
            orderToSelect += "C1";
            earnings += (c1Cost * sellPercent);
            break;

        case 2:
            orderToSelect += "C2";
            earnings += (c2Cost * sellPercent);
            break;

        case 3:
            orderToSelect += "C3";
            earnings += (c3Cost * sellPercent);
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
    TArray<FOrdersForProduction> ordersForDayProduction;
    expectedEarnings = expected;

    for(int i = 0; i < selectedOrders.Num(); i ++)
    {
        FString order = FString::FromInt(gneratedOrders[selectedOrders[i]].orderQuantity) + " X " 
                            + gneratedOrders[selectedOrders[i]].selectionOrder;

        ordersByIndex.Add(order);
        
        FOrdersForProduction orderSelected;
        orderSelected.orderForProductionQuantity = gneratedOrders[selectedOrders[i]].orderQuantity;
        orderSelected.orderForProductionCode = gneratedOrders[selectedOrders[i]].selectionOrder;

        ordersForDayProduction.Add(orderSelected);
    }

    if(storageManager)
    {
        storageManager->GetOrdersOfTheDay(ordersForDayProduction);
    }
    initialSeconds = GetWorld()->GetDeltaSeconds();

}

// Updates the order status on screen, this is based on the order being produced on the production line.
void AManagerComputer::UpdateOrderProductionStatusOnScreen(FString orderInProduction)
{
    if(currentOrderScreen->GetProductionOrderOnScreen().IsEmpty())
    {
        currentOrderScreen->SetProductionOrderOnScreen(orderInProduction);
    }else if(!currentOrderScreen->GetProductionOrderOnScreen().Equals(orderInProduction))
    {
        lastOrderScreen->SetProductionOrderOnScreen(currentOrderScreen->GetProductionOrderOnScreen());
        currentOrderScreen->SetProductionOrderOnScreen(orderInProduction);
    }

}

///////////////////////////////////// OIL & LUBRICANT SUPPLY PROPERTIES ////////////////////////////////
// Section for oil and Lubricant supply.

// Calculates the current money and then if enough, set boolenan to buy on Refueler Computer.
void AManagerComputer::CalculateOilTransaction(float oilCost)
{
    UE_LOG(LogTemp, Display, TEXT("ASKING OIL"));
    if((currentMoney - oilCost) >= 0)
    {
        UE_LOG(LogTemp, Display, TEXT("MONEY AFTER ASKING OIL: %f"), currentMoney - oilCost);
        if(refuelerComputer)
        {
            UE_LOG(LogTemp, Display, TEXT("BUYING OIL"));
            refuelerComputer->SetOilTransaction(true);
        }
        currentMoney -= oilCost;
    }

}

// Calculates the current money and then if enough, set boolenan to buy on Refueler Computer.
void AManagerComputer::CalculateLubricantTransaction(float lubricantCost)
{
    UE_LOG(LogTemp, Display, TEXT("ASKING LUBRICANT"));
    if((currentMoney - lubricantCost) >= 0)
    {
        UE_LOG(LogTemp, Display, TEXT("MONEY AFTER ASKING LUBRICANT: %f"), currentMoney - lubricantCost);
        if(refuelerComputer)
        {
            UE_LOG(LogTemp, Display, TEXT("BUYING LUBRICANT"));
            refuelerComputer->SetOilTransaction(true);
        }
        currentMoney -= lubricantCost;
    }

}

///////////////////////////////////// RESET SELECTION ORDERS COST PROPERTIES ////////////////////////////////
// Section for reset orders options and cost.

// By a Reset button in Widget Supplier ask for new codes to select.
void AManagerComputer::RegenerateTheOrdersToSelect()
{
    if((currentMoney - resetCost >= 0) && computerWidget)
    {
        currentMoney -= resetCost;
        GenerateOrdersForTheDay();
        computerWidget->SetOrdersToSelect(gneratedOrders);
    }
    
}

///////////////////////////////////// EXIT SIMULATION INFO PROPERTIES ////////////////////////////////
// Section for data recovering to display on Exit Door Widget.

// Gather all the information to pass on to Exit Door.
FExitSimulationInfo AManagerComputer::GetExitDoorInformation()
{
    if(storageManager)
    {
        exitPlayerInfo.timeSimulated = GetWorld()->GetDeltaSeconds() - initialSeconds;

        exitPlayerInfo.totalProducts = storageManager->GetTotalAmountOfProducedProducts();

        exitPlayerInfo.mostProduced = storageManager->GetMaxProducedCode();

        exitPlayerInfo.totalEarnings = currentMoney - initialMoney;

        exitPlayerInfo.lostMoney = lossMoney;
    }
    return exitPlayerInfo;

}
