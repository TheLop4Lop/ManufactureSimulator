// Fill out your copyright notice in the Description page of Project Settings.


#include "InitialPiece.h"

void AInitialPiece::SetQuantityProduction(int& Quantity)
{
    InitialQuantity = Quantity;

}

int AInitialPiece::GetQuantityProduction()
{
    return InitialQuantity;

}
