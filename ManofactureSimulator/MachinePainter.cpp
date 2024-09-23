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

        EMachineStatus NewStatus = EMachineStatus::ON_PRODUCTION;

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

	switch (GetStringToEnumFormMap(properties.Right(2)))
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

    switch (GetStringToEnumColorMap(codeToProcess.Right(2)))
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
        case EProductMaterial::M1:
            productCode += "M1";
            break;
        
        case EProductMaterial::M2:
            productCode += "M2";
            break;

        case EProductMaterial::M3:
            productCode += "M3";
            break;

        default:
            break;
        }

        switch (paintedProductCode.Size)
        {
        case EProductSize::S1:
            productSizeToSpawn = productSize[0];
            productCode += "S1";
            break;
        
        case EProductSize::S2:
            productSizeToSpawn = productSize[1];
            productCode += "S2";
            break;

        case EProductSize::S3:
            productSizeToSpawn = productSize[2];
            productCode += "S3";
            break;

        default:
            break;
        }

        switch (paintedProductCode.Form)
        {
        case EProductForm::F1:
            productMeshToSpawn = productMesh[0];
            productCode += "F1";
            break;
        
        case EProductForm::F2:
            productMeshToSpawn = productMesh[1];
            productCode += "F2";
            break;

        case EProductForm::F3:
            productMeshToSpawn = productMesh[2];
            productCode += "F3";
            break;

        default:
            break;
        }

        switch (paintedProductCode.Color)
        {
        case EProductColor::C1: // BLUE COLOR
            switch (paintedProductCode.Quality)
            {
            case EProductMaterial::M1:
                productMaterialToSpawn = color1Quality[0];
                break;
            
            case EProductMaterial::M2:
                productMaterialToSpawn = color2Quality[0];
                break;

            case EProductMaterial::M3:
                productMaterialToSpawn = color3Quality[0];
                break;

            default:
                break;
            }// End of Quality Switch in C1
            productCode += "C1";
            break;
        
        case EProductColor::C2:// RED COLOR
            switch (paintedProductCode.Quality)
            {
            case EProductMaterial::M1:
                productMaterialToSpawn = color1Quality[1];
                break;
            
            case EProductMaterial::M2:
                productMaterialToSpawn = color2Quality[1];
                break;

            case EProductMaterial::M3:
                productMaterialToSpawn = color3Quality[1];
                break;

            default:
                break;
            }// End of Quality Switch in C2
            productCode += "C2";
            break;

        case EProductColor::C3: // GREEN COLOR
            switch (paintedProductCode.Quality)
            {
            case EProductMaterial::M1:
                productMaterialToSpawn = color1Quality[2];
                break;
            
            case EProductMaterial::M2:
                productMaterialToSpawn = color2Quality[2];
                break;

            case EProductMaterial::M3:
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
            paintedProduct->SetProductQuality(productsQuality[deleteIndex] - lubricantPenalty);
            productsQuality[deleteIndex] = 0;
            deleteIndex = 0;
        }else if(productsQuality[deleteIndex] != 0)
        {
            paintedProduct->SetProductQuality(productsQuality[deleteIndex] - lubricantPenalty);
            productsQuality[deleteIndex] = 0;
            deleteIndex++;
        }

        productsToProcess --;
    }

}
