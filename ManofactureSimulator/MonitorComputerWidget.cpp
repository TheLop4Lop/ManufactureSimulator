// Fill out your copyright notice in the Description page of Project Settings.


#include "MonitorComputerWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

// Method to recieve data from player to show information on widget.
void UMonitorComputerWidget::SetOrderOTDsStatus(TArray<FString> ordersOTD, TArray<FOrderOTD> ordersOTDStatus)
{
    UImage* orderImages[6] = {ImageIndex0, ImageIndex1, ImageIndex2, ImageIndex3, ImageIndex4, ImageIndex5};

    UTextBlock* orderNames[6] = {orderIndex0, orderIndex1, orderIndex2, orderIndex3, orderIndex4, orderIndex5};
    UTextBlock* orderStock[6] = {stockIndex0, stockIndex1, stockIndex2, stockIndex3, stockIndex4, stockIndex5};
    
    UTextBlock* orderL1s[6] = {l1Index0, l1Index1, l1Index2, l1Index3, l1Index4, l1Index5};
    UTextBlock* orderL2s[6] = {l2Index0, l2Index1, l2Index2, l2Index3, l2Index4, l2Index5};
    UTextBlock* orderL3s[6] = {l3Index0, l3Index1, l3Index2, l3Index3, l3Index4, l3Index5};

    for(int i = 0; i < ordersOTD.Num(); i++)
    {
        FSlateColor colorStatus(ordersOTDStatus[i].orderColorStatus);
        orderImages[i]->SetBrushTintColor(colorStatus);

        FString preOrder = "Order : ";
        orderNames[i]->SetText(FText::FromString(preOrder + ordersOTD[i]));

        preOrder = "Stock: ";
        orderStock[i]->SetText(FText::FromString(preOrder + FString::FromInt(ordersOTDStatus[i].canProduceByStock)));

        orderL1s[i]->SetText(FText::FromString(FString::FromInt(ordersOTDStatus[i].lxProperties[0]))); // index 0 correspond to L1s in the array.
        orderL2s[i]->SetText(FText::FromString(FString::FromInt(ordersOTDStatus[i].lxProperties[1]))); // index 1 correspond to L1s in the array.
        orderL3s[i]->SetText(FText::FromString(FString::FromInt(ordersOTDStatus[i].lxProperties[2]))); // index 2 correspond to L1s in the array.
    }

}

// Set the amount of money produced by the factory.
void UMonitorComputerWidget::UMonitorComputerWidget::SetEarnings(float money)
{
    playerMoney->SetText(FText::AsNumber(money));

}
