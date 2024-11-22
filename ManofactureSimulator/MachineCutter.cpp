// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineCutter.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "CuttedProduct.h"
#include "RawProduct.h"

///////////////////////////////////// PRODUCT PROCESS ////////////////////////////////
// Section for all the logic in process the product.

void AMachineCutter::CheckEntranceForProduct()
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
                ARawProduct* productOnEntrance = Cast<ARawProduct>(singleActor);
                if (productOnEntrance->GetProductCode().Equals(codeToProcess))
                {
                    if (productOnEntrance && productsToProcess < maxProductOrder) // THIS CHANGE DEPENDING ON THE MACHINE
                    {
                        ManageInitialProductProperties(productOnEntrance->GetProductCode());
                        InsertQualityToArray(productOnEntrance->GetProductQuality());
                        productOnEntrance->DestroyProduct();
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
                break; // Exit the loop once we find a valid product
            }
            else
            {
                NewStatus = EMachineStatus::PRODUCT_ERROR;
            }
        }

        // Call ChangeProductionStatus only if the status has changed
        if (NewStatus != PreviousStatus)
        {
            ChangeProductionStatus(NewStatus);
            PreviousStatus = NewStatus;
        }
    }
}

// Checks and store quality values from pieces into the productsQuality array.
void AMachineCutter::InsertQualityToArray(int pieceQuality)
{
    productsQuality[insertIndex] = pieceQuality;

}

// Gets the initialPieceAtributes and convert it to BaseMachine product code.
void AMachineCutter::ManageInitialProductProperties(FString properties)
{
    switch (UEProductProperties::ConverStringToEnumQuality(properties.Left(2)))
    {
    case EPieceMaterial::QUALITY_LOW:
        cuttedProductCode.Quality = EPieceMaterial::QUALITY_LOW;
        timeByMaterial = timeByMaterialLow;
        break;
	case EPieceMaterial::QUALITY_MEDIUM:
        cuttedProductCode.Quality = EPieceMaterial::QUALITY_MEDIUM;
        timeByMaterial = timeByMaterialMidd;
        break;
	case EPieceMaterial::QUALITY_HIGH:
        cuttedProductCode.Quality = EPieceMaterial::QUALITY_HIGH;
        timeByMaterial = timeByMaterialHigh;
        break;
    
    default:
        break;
    }

	switch (UEProductProperties::ConverStringToEnumSize(properties.Mid(2, 2)))
    {
    case EPieceSize::SIZE_SMALL:
        cuttedProductCode.Size = EPieceSize::SIZE_SMALL;
        timeBySize = timeBySizeLow;
        break;
	case EPieceSize::SIZE_MEDIUM:
        cuttedProductCode.Size = EPieceSize::SIZE_MEDIUM;
        timeBySize = timeBySizeMidd;
        break;
	case EPieceSize::SIZE_BIG:
        cuttedProductCode.Size = EPieceSize::SIZE_BIG;
        timeBySize = timeBySizeHigh;
        break;
    
    default:
        break;
    }

	switch (UEProductProperties::ConverStringToEnumLength(properties.Right(2)))
    {
    case EPieceLenght::LENGTH_SHORT:
        productsToProcess += 3;
        break;
	case EPieceLenght::LENGTH_MEDIUM:
        productsToProcess += 5;
        break;
	case EPieceLenght::LENGTH_LARGE:
        productsToProcess += 10;
        break;

    default:
        break;
    }
    
    totalProductionPerPiece = timeByMaterial + timeBySize + oilPenalty;

}

///////////////////////////////////// SPAWN PRODUCT ////////////////////////////////
// Section for spawn product and set properties.

// Spawn product based on a specific ABaseProduct child, dependes on the process and machine.
void AMachineCutter::SpawnProducedProduct()
{  
    UStaticMesh* productMeshToSpawn = nullptr;
    FVector productSizeToSpawn = FVector::ZeroVector;
    UMaterial* productMaterialToSpawn = nullptr;
    FString productCode = "";
    
    if(productMesh.Num() > 0 && productSize.Num() > 2 && qualityMaterial.Num() > 2)
	{
        productMeshToSpawn = productMesh[0];
		switch (cuttedProductCode.Quality)
        {
        case EPieceMaterial::QUALITY_LOW:
            productMaterialToSpawn = qualityMaterial[0];
            productCode += "M1";
            break;
        
        case EPieceMaterial::QUALITY_MEDIUM:
            productMaterialToSpawn = qualityMaterial[1];
            productCode += "M2";
            break;

        case EPieceMaterial::QUALITY_HIGH:
            productMaterialToSpawn = qualityMaterial[2];
            productCode += "M3";
            break;

        default:
            break;
        }

        switch (cuttedProductCode.Size)
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
	}

    if(productClass)
    {
        ACuttedProduct* cuttedProduct = GetWorld()->SpawnActor<ACuttedProduct>(productClass, boxExit->GetComponentLocation(), boxExit->GetComponentRotation());
        cuttedProduct->SetsProductProperties(productMeshToSpawn, productMaterialToSpawn, productSizeToSpawn);
        cuttedProduct->SetProductCode(productCode);

        if(productsToProcess != 0)
        {
            cuttedProduct->SetProductQuality(FMath::Max(0, productsQuality[0] - lubricantPenalty));
        }else
        {
            productsQuality[deleteIndex] = 0;
        }

        productsToProcess --;
    }

}
