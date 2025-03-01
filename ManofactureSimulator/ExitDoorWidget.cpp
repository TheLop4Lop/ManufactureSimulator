// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitDoorWidget.h"

// Set production time in seconds
void UExitDoorWidget::SetPlayerTimeInProduction(float productionPlayed)
{
    playerTimeProduction = productionPlayed;

}

// Set the max productes produced in the sesion.
void UExitDoorWidget::SetTotalProductsProduced(int totalProducts)
{
    playerProductsProduced = totalProducts;

}

// Set the code of the product with more pproduction in storage.
void UExitDoorWidget::SetMostProducedProduct(FString productCode)
{
    playerMostProducedProduct = productCode;

}

// Set the total amount of earnings.
void UExitDoorWidget::SetTotalEarnings(float totalEarnings)
{
    earnings = totalEarnings;

}

// Set the lost money through production, based on player's mistakes.
void UExitDoorWidget::SetLostMoney(float lost)
{
    lostMoney = lost;

}
