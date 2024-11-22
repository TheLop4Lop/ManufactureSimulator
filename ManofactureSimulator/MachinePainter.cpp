// Fill out your copyright notice in the Description page of Project Settings.


#include "MachinePainter.h"
#include "Components/BoxComponent.h"
#include "MolderedProduct.h"
#include "PaintedProduct.h"

//////////////////////////////////// PRODUCT PROCESS ////////////////////////////////
// Section for all the logic in process the product.

void AMachinePainter::CheckEntranceForProduct()
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
                AMolderedProduct* productOnEntrance = Cast<AMolderedProduct>(singleActor);
                if (productOnEntrance->GetProductCode().Equals(codeToProcess.Left(6)))
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
void AMachinePainter::ManageMolderedProductProperties(FString properties)
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

	switch (UEProductProperties::ConverStringToEnumForm(properties.Right(2)))
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

    switch (UEProductProperties::ConverStringToEnumColor(codeToProcess.Right(2)))
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
    
    totalProductionPerPiece = timeByMaterial + timeBySize + timeByForm + timeByColor + oilPenalty;

}

///////////////////////////////////// SPAWN PRODUCT ////////////////////////////////
// Section for spawn product and set properties.

// Spawn product based on a specific ABaseProduct child, dependes on the process and machine.
void AMachinePainter::SpawnProducedProduct()
{  
    UStaticMesh* productMeshToSpawn = nullptr;
    FVector productSizeToSpawn = FVector::ZeroVector;
    UMaterial* productMaterialToSpawn = nullptr;
    FString productCode = "";
    
    if(productMesh.Num() > 2 && productSize.Num() > 2 && color1Quality.Num() > 2 && color2Quality.Num() > 2 && color3Quality.Num() > 2)
	{
        switch (paintedProductCode.Quality)
        {
        case EPieceMaterial::QUALITY_LOW:
            productCode += "M1";
            break;
        
        case EPieceMaterial::QUALITY_MEDIUM:
            productCode += "M2";
            break;

        case EPieceMaterial::QUALITY_HIGH:
            productCode += "M3";
            break;

        default:
            break;
        }

        switch (paintedProductCode.Size)
        {
        case EPieceSize::SIZE_SMALL:
            productSizeToSpawn = productSize[0];
            productCode += "S1";
            break;
        
        case EPieceSize::SIZE_MEDIUM:
            productSizeToSpawn = productSize[1];
            productCode += "S2";
            break;

        case EPieceSize::SIZE_BIG:
            productSizeToSpawn = productSize[2];
            productCode += "S3";
            break;

        default:
            break;
        }

        switch (paintedProductCode.Form)
        {
        case EPieceForm::FORM_CONE:
            productMeshToSpawn = productMesh[0];
            productCode += "F1";
            break;
        
        case EPieceForm::FORM_CYLINDER:
            productMeshToSpawn = productMesh[1];
            productCode += "F2";
            break;

        case EPieceForm::FORM_TORUS:
            productMeshToSpawn = productMesh[2];
            productCode += "F3";
            break;

        default:
            break;
        }

        switch (paintedProductCode.Color)
        {
        case EPieceColor::COLOR_BLUE: // BLUE COLOR
            switch (paintedProductCode.Quality)
            {
            case EPieceMaterial::QUALITY_LOW:
                productMaterialToSpawn = color1Quality[0];
                break;
            
            case EPieceMaterial::QUALITY_MEDIUM:
                productMaterialToSpawn = color2Quality[0];
                break;

            case EPieceMaterial::QUALITY_HIGH:
                productMaterialToSpawn = color3Quality[0];
                break;

            default:
                break;
            }// End of Quality Switch in C1
            productCode += "C1";
            break;
        
        case EPieceColor::COLOR_RED:// RED COLOR
            switch (paintedProductCode.Quality)
            {
            case EPieceMaterial::QUALITY_LOW:
                productMaterialToSpawn = color1Quality[1];
                break;
            
            case EPieceMaterial::QUALITY_MEDIUM:
                productMaterialToSpawn = color2Quality[1];
                break;

            case EPieceMaterial::QUALITY_HIGH:
                productMaterialToSpawn = color3Quality[1];
                break;

            default:
                break;
            }// End of Quality Switch in C2
            productCode += "C2";
            break;

        case EPieceColor::COLOR_GREEN: // GREEN COLOR
            switch (paintedProductCode.Quality)
            {
            case EPieceMaterial::QUALITY_LOW:
                productMaterialToSpawn = color1Quality[2];
                break;
            
            case EPieceMaterial::QUALITY_MEDIUM:
                productMaterialToSpawn = color2Quality[2];
                break;

            case EPieceMaterial::QUALITY_HIGH:
                productMaterialToSpawn = color3Quality[2];
                break;

            default:
                break;
            }// End of Quality Switch in C3
            productCode += "C3";
            break;

        default:
            break;
        }
	}

    if(productClass)
    {
        APaintedProduct* paintedProduct = GetWorld()->SpawnActor<APaintedProduct>(productClass, boxExit->GetComponentLocation(), boxExit->GetComponentRotation());
        paintedProduct->SetsProductProperties(productMeshToSpawn, productMaterialToSpawn, productSizeToSpawn);
        paintedProduct->SetProductCode(productCode);

        if(deleteIndex == productsQuality.Num() - 1 && productsQuality[deleteIndex] != 0)
        {
            paintedProduct->SetProductQuality(FMath::Max(0, productsQuality[deleteIndex] - lubricantPenalty));
            productsQuality[deleteIndex] = 0;
            deleteIndex = 0;
        }else if(productsQuality[deleteIndex] != 0)
        {
            paintedProduct->SetProductQuality(FMath::Max(0, productsQuality[deleteIndex] - lubricantPenalty));
            productsQuality[deleteIndex] = 0;
            deleteIndex++;
        }

        productsToProcess --;
    }

}
