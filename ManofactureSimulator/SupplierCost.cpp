// Fill out your copyright notice in the Description page of Project Settings.


#include "SupplierCost.h"
#include "EProductProperties.h"

SupplierCost::SupplierCost()
{
}

SupplierCost::~SupplierCost()
{
}

// Returns simple cost of Material Quality.
float SupplierCost::CalculateMaterialQualityCost(FString materialCode, int quantity)
{
    float materialCost = 0.0f;
    switch(UEProductProperties::ConverStringToEnumQuality(materialCode))
    {
        case EPieceMaterial::QUALITY_LOW:
            materialCost = 10.0f;
            break;

        case EPieceMaterial::QUALITY_MEDIUM:
            materialCost = 15.5f;
            break;

        case EPieceMaterial::QUALITY_HIGH:
            materialCost = 20.0f;
            break;

        default:
            materialCost = 0.0f;
            break;
    }

    return materialCost * CalculateDiscount(quantity);

}

// Returns simple cost of Material Size.
float SupplierCost::CalculateMaterialSizeCost(FString sizeCode, int quantity)
{
    float sizeCost = 0.0f;
    switch(UEProductProperties::ConverStringToEnumSize(sizeCode))
    {
        case EPieceSize::SIZE_SMALL:
            sizeCost = 5.0f;
            break;

        case EPieceSize::SIZE_MEDIUM:
            sizeCost = 10.5f;
            break;

        case EPieceSize::SIZE_BIG:
            sizeCost = 15.5f;
            break;

        default:
            sizeCost = 0.0f;
            break;
    }

    return sizeCost * CalculateDiscount(quantity);

}

// Returns simple cost of Material Length.
float SupplierCost::CalculateMaterialLengthCost(FString lengthCode, int quantity)
{
    float lengthCost = 0.0f;
    switch(UEProductProperties::ConverStringToEnumLength(lengthCode))
    {
        case EPieceLenght::LENGTH_SHORT:
            lengthCost = 20.5f;
            break;

        case EPieceLenght::LENGTH_MEDIUM:
            lengthCost = 40.5f;
            break;

        case EPieceLenght::LENGTH_LARGE:
            lengthCost = 60.5f;
            break;

        default:
            lengthCost = 0.0f;
            break;
    }

    return lengthCost * CalculateDiscount(quantity);

}

// Returns the total value of the order code.
float SupplierCost::CalculateTotalOrderCost(FString orderCode, int quantity)
{
    return CalculateMaterialQualityCost(orderCode.Left(2), quantity) + 
            CalculateMaterialSizeCost(orderCode.Mid(2,2), quantity) + 
                CalculateMaterialLengthCost(orderCode.Right(2), quantity);

}

// Gets Discount per quantity.
float SupplierCost::CalculateDiscount(int quantity)
{
    switch (quantity)
    {
    case 10:
        return (float)quantity * 0.7f;
    case 9:
        return (float)quantity * 0.8f;
    case 8:
        return (float)quantity * 0.9f;
    default:
        break;
    }

    return (float)quantity;

}
