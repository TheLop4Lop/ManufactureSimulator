// Fill out your copyright notice in the Description page of Project Settings.


#include "ManagerSupplierWidget.h"
#include "SupplierCost.h"

// Sets the value of qualityMaterialCost.
void UManagerSupplierWidget::SetValueofCurrentMoney(float money)
{
    currentMoney = money;

}

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
