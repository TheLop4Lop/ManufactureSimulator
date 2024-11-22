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
    switch (UEProductProperties::ConverStringToEnumQuality(properties.Left(2)))
    {
    case EPieceMaterial::QUALITY_LOW:
        paintedProductCode.Quality = EPieceMaterial::QUALITY_LOW;
        timeByMaterial = timeByMaterialLow;
        break;
	case EPieceMaterial::QUALITY_MEDIUM:
        paintedProductCode.Quality = EPieceMaterial::QUALITY_MEDIUM;
        timeByMaterial = timeByMaterialMidd;
        break;
	case EPieceMaterial::QUALITY_HIGH:
        paintedProductCode.Quality = EPieceMaterial::QUALITY_HIGH;
        timeByMaterial = timeByMaterialHigh;
        break;
    
    default:
        break;
    }

	switch (UEProductProperties::ConverStringToEnumSize(properties.Mid(2, 2)))
    {
    case EPieceSize::SIZE_SMALL:
        paintedProductCode.Size = EPieceSize::SIZE_SMALL;
        timeBySize = timeBySizeLow;
        break;
	case EPieceSize::SIZE_MEDIUM:
        paintedProductCode.Size = EPieceSize::SIZE_MEDIUM;
        timeBySize = timeBySizeMidd;
        break;
	case EPieceSize::SIZE_BIG:
        paintedProductCode.Size = EPieceSize::SIZE_BIG;
        timeBySize = timeBySizeHigh;
        break;
    
    default:
        break;
    }

	switch (UEProductProperties::ConverStringToEnumForm(properties.Mid(4, 2)))
    {
    case EPieceForm::FORM_CONE:
        paintedProductCode.Form = EPieceForm::FORM_CONE;
        timeByForm = timeByFormF1;
        break;
	case EPieceForm::FORM_CYLINDER:
        paintedProductCode.Form = EPieceForm::FORM_CYLINDER;
        timeByForm = timeByFormF2;
        break;
	case EPieceForm::FORM_TORUS:
        paintedProductCode.Form = EPieceForm::FORM_TORUS;
        timeByForm = timeByFormF3;
        break;

    default:
        break;
    }

    switch (UEProductProperties::ConverStringToEnumColor(properties.Right(2)))
    {
    case EPieceColor::COLOR_BLUE:
        paintedProductCode.Color = EPieceColor::COLOR_BLUE;
        timeByColor = timeByColorC1;
        break;
	case EPieceColor::COLOR_RED:
        paintedProductCode.Color = EPieceColor::COLOR_RED;
        timeByColor = timeByColorC2;
        break;
	case EPieceColor::COLOR_GREEN:
        paintedProductCode.Color = EPieceColor::COLOR_GREEN;
        timeByColor = timeByColorC3;
        break;

    default:
        break;
    }
    
    totalProductionPerPiece = timeByMaterial + timeBySize + timeByForm + timeByColor;

}
