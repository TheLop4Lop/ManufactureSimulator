// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineOven.h"
#include "Components/BoxComponent.h"
#include "PaintedProduct.h"

//////////////////////////////////// PRODUCT PROCESS ////////////////////////////////
// Section for all the logic in process the product.

void AMachineOven::CheckEntranceForProduct()
{
    if (boxEntrance)
    {
        TArray<AActor*> actorsOnEntrance;
        boxEntrance->GetOverlappingActors(actorsOnEntrance);

        EMachineStatus NewStatus;
        (productsToProcess > 0)? NewStatus = EMachineStatus::ON_PRODUCTION : NewStatus = EMachineStatus::ON_HOLD;

        for (AActor* singleActor : actorsOnEntrance)
        {
            if (singleActor && singleActor->IsA(classToTransform))
            {
                APaintedProduct* productOnEntrance = Cast<APaintedProduct>(singleActor);
                if (productOnEntrance->GetProductCode().Equals(codeToProcess))
                {
                    if (productOnEntrance && productsToProcess < maxProductOrder) // THIS CHANGE DEPENDING ON THE MACHINE
                    {
                        ManageMolderedProductProperties(productOnEntrance->GetProductCode());
                        InsertQualityToArray(productOnEntrance->GetProductQuality());
                        
                        productOnEntrance->DestroyProduct();
                        productsToProcess++;
                    }
                    else
                    {
                        NewStatus = EMachineStatus::FULL_PRODUCTION;
                    }
                }
                else
                {
                    NewStatus = EMachineStatus::CODE_ERROR;
                    UE_LOG(LogTemp, Error, TEXT("Product Code: %s"), *productOnEntrance->GetProductCode());
                    UE_LOG(LogTemp, Error, TEXT("Machine Code: %s"), *codeToProcess);
                }
                break;
            }
            else
            {
                NewStatus = EMachineStatus::PRODUCT_ERROR;
            }
        }

        if (NewStatus != PreviousStatus)
        {
            ChangeProductionStatus(NewStatus);
            PreviousStatus = NewStatus;
        }
    }
}

// Gets the cuttedProduct properties and proces production product code.
void AMachineOven::ManageMolderedProductProperties(FString properties)
{
    switch (GetStringToEnumMaterialMap(properties.Left(2)))
    {
    case EProductMaterial::M1:
        paintedProductCode.Quality = EProductMaterial::M1;
        timeByMaterial = timeByMaterialLow;
        break;
	case EProductMaterial::M2:
        paintedProductCode.Quality = EProductMaterial::M2;
        timeByMaterial = timeByMaterialMidd;
        break;
	case EProductMaterial::M3:
        paintedProductCode.Quality = EProductMaterial::M3;
        timeByMaterial = timeByMaterialHigh;
        break;
    
    default:
        break;
    }

	switch (GetStringToEnumSizeMap(properties.Mid(2, 2)))
    {
    case EProductSize::S1:
        paintedProductCode.Size = EProductSize::S1;
        timeBySize = timeBySizeLow;
        break;
	case EProductSize::S2:
        paintedProductCode.Size = EProductSize::S2;
        timeBySize = timeBySizeMidd;
        break;
	case EProductSize::S3:
        paintedProductCode.Size = EProductSize::S3;
        timeBySize = timeBySizeHigh;
        break;
    
    default:
        break;
    }

	switch (GetStringToEnumFormMap(properties.Mid(4, 2)))
    {
    case EProductForm::F1:
        paintedProductCode.Form = EProductForm::F1;
        timeByForm = timeByFormF1;
        break;
	case EProductForm::F2:
        paintedProductCode.Form = EProductForm::F2;
        timeByForm = timeByFormF2;
        break;
	case EProductForm::F3:
        paintedProductCode.Form = EProductForm::F3;
        timeByForm = timeByFormF3;
        break;

    default:
        break;
    }

    switch (GetStringToEnumColorMap(properties.Right(2)))
    {
    case EProductColor::C1:
        paintedProductCode.Color = EProductColor::C1;
        timeByColor = timeByColorC1;
        break;
	case EProductColor::C2:
        paintedProductCode.Color = EProductColor::C2;
        timeByColor = timeByColorC2;
        break;
	case EProductColor::C3:
        paintedProductCode.Color = EProductColor::C3;
        timeByColor = timeByColorC3;
        break;

    default:
        break;
    }
    
    totalProductionPerPiece = timeByMaterial + timeBySize + timeByForm + timeByColor;

}
