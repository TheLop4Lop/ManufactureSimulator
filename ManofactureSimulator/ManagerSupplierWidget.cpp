// Fill out your copyright notice in the Description page of Project Settings.


#include "ManagerSupplierWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "SupplierCost.h"

void UManagerSupplierWidget::NativeConstruct()
{
    Super::NativeConstruct();

    ImplementButtons();
    ImplementAcceptButton();

}

///////////////////////////////////// MONEY PROPERTIES ////////////////////////////////
// Section for buying material.

// Gets from blueprint the material code value;
void UManagerSupplierWidget::SetMaterialCost(FString qualityCode)
{
    qualityCostCode = qualityCode;

}

// Gets from blueprint the size code value;
void UManagerSupplierWidget::SetSizeCost(FString sizeCode)
{
    sizeCostCode = sizeCode;
    
}

// Gets from blueprint the length code value;
void UManagerSupplierWidget::SetLengthCost(FString lengthCode)
{
    lengthCostCode = lengthCode;

}

// Updates Value of totalMaterialCost.
void UManagerSupplierWidget::UpdateTotalMaterialCostValue(int orderQuantity)
{
    (!qualityCostCode.IsEmpty())? qualityMaterialCost = SupplierCost::CalculateMaterialQualityCost(qualityCostCode, orderQuantity) : qualityMaterialCost = 0.0f;
    (!sizeCostCode.IsEmpty())? sizeMaterialCost = SupplierCost::CalculateMaterialSizeCost(sizeCostCode, orderQuantity) : sizeMaterialCost = 0.0f;
    (!lengthCostCode.IsEmpty())? lengthMaterialCost = SupplierCost::CalculateMaterialLengthCost(lengthCostCode, orderQuantity) : lengthMaterialCost = 0.0f;

    UE_LOG(LogTemp, Display, TEXT("QUANTITY: %i, QUALITY COST: %f, SIZE COST: %f, LENGTH COST: %f"), orderQuantity, qualityMaterialCost, sizeMaterialCost, lengthMaterialCost);
    totalMaterialCost = qualityMaterialCost + sizeMaterialCost + lengthMaterialCost;

}

///////////////////////////////////// ORDER SELECTION PROPERTIES ////////////////////////////////
// Section for order selection proccess.

// Sets buttons implementation.
void UManagerSupplierWidget::ImplementButtons()
{
    if(buttonOrder)
    {
        buttonOrder->OnPressed.AddDynamic(this, &UManagerSupplierWidget::SetButtonOrderLogic);
    }

    if(buttonOrder_1)
    {
        buttonOrder_1->OnPressed.AddDynamic(this, &UManagerSupplierWidget::SetButtonOrderLogic_1);
    }

    if(buttonOrder_2)
    {
        buttonOrder_2->OnPressed.AddDynamic(this, &UManagerSupplierWidget::SetButtonOrderLogic_2);
    }

    if(buttonOrder_3)
    {
        buttonOrder_3->OnPressed.AddDynamic(this, &UManagerSupplierWidget::SetButtonOrderLogic_3);
    }

    if(buttonOrder_4)
    {
        buttonOrder_4->OnPressed.AddDynamic(this, &UManagerSupplierWidget::SetButtonOrderLogic_4);
    }

    if(buttonOrder_5)
    {
        buttonOrder_5->OnPressed.AddDynamic(this, &UManagerSupplierWidget::SetButtonOrderLogic_5);
    }

    if(buttonOrder_6)
    {
        buttonOrder_6->OnPressed.AddDynamic(this, &UManagerSupplierWidget::SetButtonOrderLogic_6);
    }

    if(buttonOrder_7)
    {
        buttonOrder_7->OnPressed.AddDynamic(this, &UManagerSupplierWidget::SetButtonOrderLogic_7);
    }

    if(buttonOrder_8)
    {
        buttonOrder_8->OnPressed.AddDynamic(this, &UManagerSupplierWidget::SetButtonOrderLogic_8);
    }

    if(buttonOrder_9)
    {
        buttonOrder_9->OnPressed.AddDynamic(this, &UManagerSupplierWidget::SetButtonOrderLogic_9);
    }

}

// Sets the logic for ButtonOrder.
void UManagerSupplierWidget::SetButtonOrderLogic()
{
    selectedButtonCode = FString::FromInt(orderToSelect[0].orderQuantity) + " X " + orderToSelect[0].selectionOrder;
    estimatedEarnings = orderToSelect[0].estimatedEarnings * orderToSelect[0].orderQuantity;
    UE_LOG(LogTemp, Display, TEXT("0 - selectedButtonCode: %s"), *selectedButtonCode);

}

// Sets the logic for ButtonOrder 1.
void UManagerSupplierWidget::SetButtonOrderLogic_1()
{
    selectedButtonCode = FString::FromInt(orderToSelect[1].orderQuantity) + " X " + orderToSelect[1].selectionOrder;
    estimatedEarnings = orderToSelect[1].estimatedEarnings * orderToSelect[1].orderQuantity;
    UE_LOG(LogTemp, Display, TEXT("1 - selectedButtonCode: %s"), *selectedButtonCode);

}

// Sets the logic for ButtonOrder 2.
void UManagerSupplierWidget::SetButtonOrderLogic_2()
{
    selectedButtonCode = FString::FromInt(orderToSelect[2].orderQuantity) + " X " + orderToSelect[2].selectionOrder;
    estimatedEarnings = orderToSelect[2].estimatedEarnings * orderToSelect[2].orderQuantity;
    UE_LOG(LogTemp, Display, TEXT("2 - selectedButtonCode: %s"), *selectedButtonCode);

}

// Sets the logic for ButtonOrder 3.
void UManagerSupplierWidget::SetButtonOrderLogic_3()
{
    selectedButtonCode = FString::FromInt(orderToSelect[3].orderQuantity) + " X " + orderToSelect[3].selectionOrder;
    estimatedEarnings = orderToSelect[3].estimatedEarnings * orderToSelect[3].orderQuantity;
    UE_LOG(LogTemp, Display, TEXT("3 - selectedButtonCode: %s"), *selectedButtonCode);

}

// Sets the logic for ButtonOrder 4.
void UManagerSupplierWidget::SetButtonOrderLogic_4()
{
    selectedButtonCode = FString::FromInt(orderToSelect[4].orderQuantity) + " X " + orderToSelect[4].selectionOrder;
    estimatedEarnings = orderToSelect[4].estimatedEarnings * orderToSelect[4].orderQuantity;
    UE_LOG(LogTemp, Display, TEXT("4 - selectedButtonCode: %s"), *selectedButtonCode);

}

// Sets the logic for ButtonOrder 5.
void UManagerSupplierWidget::SetButtonOrderLogic_5()
{
    selectedButtonCode = FString::FromInt(orderToSelect[5].orderQuantity) + " X " + orderToSelect[5].selectionOrder;
    estimatedEarnings = orderToSelect[5].estimatedEarnings * orderToSelect[5].orderQuantity;
    UE_LOG(LogTemp, Display, TEXT("5 - selectedButtonCode: %s"), *selectedButtonCode);

}

// Sets the logic for ButtonOrder 6.
void UManagerSupplierWidget::SetButtonOrderLogic_6()
{
    selectedButtonCode = FString::FromInt(orderToSelect[6].orderQuantity) + " X " + orderToSelect[6].selectionOrder;
    estimatedEarnings = orderToSelect[6].estimatedEarnings * orderToSelect[6].orderQuantity;
    UE_LOG(LogTemp, Display, TEXT("6 - selectedButtonCode: %s"), *selectedButtonCode);

}

// Sets the logic for ButtonOrder 7.
void UManagerSupplierWidget::SetButtonOrderLogic_7()
{
    selectedButtonCode = FString::FromInt(orderToSelect[7].orderQuantity) + " X " + orderToSelect[7].selectionOrder;
    estimatedEarnings = orderToSelect[7].estimatedEarnings * orderToSelect[7].orderQuantity;
    UE_LOG(LogTemp, Display, TEXT("7 - selectedButtonCode: %s"), *selectedButtonCode);

}

// Sets the logic for ButtonOrder 8.
void UManagerSupplierWidget::SetButtonOrderLogic_8()
{
    selectedButtonCode = FString::FromInt(orderToSelect[8].orderQuantity) + " X " + orderToSelect[8].selectionOrder;
    estimatedEarnings = orderToSelect[8].estimatedEarnings * orderToSelect[8].orderQuantity;
    UE_LOG(LogTemp, Display, TEXT("8 - selectedButtonCode: %s"), *selectedButtonCode);

}

// Sets the logic for ButtonOrder 9.
void UManagerSupplierWidget::SetButtonOrderLogic_9()
{
    selectedButtonCode = FString::FromInt(orderToSelect[9].orderQuantity) + " X " + orderToSelect[9].selectionOrder;
    estimatedEarnings = orderToSelect[9].estimatedEarnings * orderToSelect[9].orderQuantity;
    UE_LOG(LogTemp, Display, TEXT("9 - selectedButtonCode: %s"), *selectedButtonCode);

}

// Set a series of orders to select from, size fixed on Max orders to select.
void UManagerSupplierWidget::SetOrdersToSelect(TArray<FOrderSelection> generatedOrders)
{
    orderToSelect.Empty(); // Empty TArray before adding new data.
    for(int i = 0; i < 10; i++)
    {
        orderToSelect.Add(generatedOrders[i]);
    }

    DisplayButtonCodeOptions();

}

// Set selected Orders from Manager Computer memory.
void UManagerSupplierWidget::DisplaySelectedOrdersFromMemory(TArray<FString> ordersSelected)
{
    UTextBlock* textButtonArray[6] = {SO_Text1, SO_Text2, SO_Text3, SO_Text4, SO_Text5, SO_Text6};
    for(int i = 0; i < 6; i++)
    {
        textButtonArray[i]->SetText(FText::FromString(ordersSelected[i]));
    }
    
    ChangeSelectedOrdersVisibility();
    orderOfTheDaySelected = true;
    
}

// Displays the Selection Code Options on button text block.
void UManagerSupplierWidget::DisplayButtonCodeOptions()
{
    UTextBlock* textButtonArray[10] = {textButton, textButton_1, textButton_2, textButton_3, textButton_4, 
                                        textButton_5, textButton_6, textButton_7, textButton_8, textButton_9};

    for(int i = 0; i < 10; i++)
    {
        FString baseTextProduct = "Product: " + orderToSelect[i].selectionOrder;
        FString baseTextQuantity ="\nQuantity: " + FString::FromInt(orderToSelect[i].orderQuantity);
        FString baseTextEarnings = "\n\nEarnings: " + FString::FromInt(orderToSelect[i].estimatedEarnings * orderToSelect[i].orderQuantity);

        textButtonArray[i]->SetText(FText::FromString(baseTextProduct + baseTextQuantity + baseTextEarnings));
    }

}

///////////////////////////////////// SELECTED ORDERS PROPERTIES ////////////////////////////////
// Section for reset orders options and cost.

// Implements Accept button logic interction.
void UManagerSupplierWidget::ImplementAcceptButton()
{
    if(acceptSelectedOrders)
    {
        acceptSelectedOrders->OnReleased.AddDynamic(this, &UManagerSupplierWidget::SetAcceptButtonLogic);
    }

}

// Set logic for Accept button.
void UManagerSupplierWidget::SetAcceptButtonLogic()
{
    if(selectionLight)
    {
        if(idexSelected.Num() == 6)
        {       
            selectionLight->SetColorAndOpacity(FColor::Green);
            orderOfTheDaySelected = true;
            for(int i = 0 ; i < idexSelected.Num(); i++)
            {
                UE_LOG(LogTemp, Display, TEXT("Selection Array: %i"), idexSelected[i]);
            }

            ordersSelectedDelegate.ExecuteIfBound(idexSelected);
        }else
        {
            selectionLight->SetColorAndOpacity(FColor::Red);
        }
    }

}

///////////////////////////////////// MONEY PROPERTIES ////////////////////////////////
// Section for buying material.

// Sets the value of qualityMaterialCost.
void UManagerSupplierWidget::SetValueofCurrentMoney(float money)
{
    currentMoney = money;

}
