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

        EMachineStatus NewStatus = EMachineStatus::ON_PRODUCTION;

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
    switch (GetStringToEnumMaterialMap(properties.Left(2)))
    {
    case EProductMaterial::M1:
        cuttedProductCode.Quality = EProductMaterial::M1;
        timeByMaterial = timeByMaterialLow;
        break;
	case EProductMaterial::M2:
        cuttedProductCode.Quality = EProductMaterial::M2;
        timeByMaterial = timeByMaterialMidd;
        break;
	case EProductMaterial::M3:
        cuttedProductCode.Quality = EProductMaterial::M3;
        timeByMaterial = timeByMaterialHigh;
        break;
    
    default:
        break;
    }

	switch (GetStringToEnumSizeMap(properties.Mid(2, 2)))
    {
    case EProductSize::S1:
        cuttedProductCode.Size = EProductSize::S1;
        timeBySize = timeBySizeLow;
        break;
	case EProductSize::S2:
        cuttedProductCode.Size = EProductSize::S2;
        timeBySize = timeBySizeMidd;
        break;
	case EProductSize::S3:
        cuttedProductCode.Size = EProductSize::S3;
        timeBySize = timeBySizeHigh;
        break;
    
    default:
        break;
    }

	switch (GetStringToEnumLengthMap(properties.Right(2)))
    {
    case EProductLength::L1:
        productsToProcess += 3;
        break;
	case EProductLength::L2:
        productsToProcess += 5;
        break;
	case EProductLength::L3:
        productsToProcess += 10;
        break;

    default:
        break;
    }
    
    totalProductionPerPiece = timeByMaterial + timeBySize;

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
        case EProductMaterial::M1:
            productMaterialToSpawn = qualityMaterial[0];
            productCode += "M1";
            break;
        
        case EProductMaterial::M2:
            productMaterialToSpawn = qualityMaterial[1];
            productCode += "M2";
            break;

        case EProductMaterial::M3:
            productMaterialToSpawn = qualityMaterial[2];
            productCode += "M3";
            break;

        default:
            break;
        }

        switch (cuttedProductCode.Size)
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
	}

    if(productClass)
    {
        ACuttedProduct* cuttedProduct = GetWorld()->SpawnActor<ACuttedProduct>(productClass, boxExit->GetComponentLocation(), boxExit->GetComponentRotation());
        cuttedProduct->SetsProductProperties(productMeshToSpawn, productMaterialToSpawn, productSizeToSpawn);
        cuttedProduct->SetProductCode(productCode);

        if(productsToProcess != 0)
        {
            cuttedProduct->SetProductQuality(productsQuality[0] - lubricantPenalty);
        }else
        {
            productsQuality[deleteIndex] = 0;
        }

        productsToProcess --;
    }

}
