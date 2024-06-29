// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineCutter.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "CuttedProduct.h"
#include "RawProduct.h"

///////////////////////////////////// PRODUCT PROCESS ////////////////////////////////
// Section for all the logic in process the product.

// Checks the actors on the boxEntrance, this will change depending on the machine.
void AMachineCutter::CheckEntranceForProduct()
{
    if (boxEntrance)
	{
		TArray<AActor*> actorsOnEntrance;
   		boxEntrance->GetOverlappingActors(actorsOnEntrance);

    	for (AActor* singleActor : actorsOnEntrance)
    	{
        	if (singleActor && singleActor->IsA(classToTransform))
        	{
				UE_LOG(LogTemp, Display, TEXT("YES"));
            	ARawProduct* productOnEntrance = Cast<ARawProduct>(singleActor);
				if((productOnEntrance && productsToProcess < maxProductOrder)) // THIS CHANGE DEPENDING ON THE MACHINE
				{
					UE_LOG(LogTemp, Display, TEXT("PADENTRO"));
                    ManageInitialProductProperties(productOnEntrance->GetRawProductCode());
					ChangeProductionStatus(EMachineStatus::ON_PRODUCTION);

					productOnEntrance->DestroyProduct();
				}else
				{
					UE_LOG(LogTemp, Display, TEXT("OCUPADO"));
					ChangeProductionStatus(EMachineStatus::FULL_PRODUCTION);
				}
        	}else
			{
				UE_LOG(LogTemp, Display, TEXT("WHAT'S THIS?"));
				ChangeProductionStatus(EMachineStatus::CODE_ERROR);
			}
    	}
	}

}

// Gets the initialPieceAtributes and convert it to BaseMachine product code.
void AMachineCutter::ManageInitialProductProperties(FInitialPieceAttribute properties)
{
    switch (properties.Quality)
    {
    case EMaterialQuality::QUALITY_LOW:
        cuttedProductCode.Quality = EProductMaterial::M1;
        timeByMaterial = timeByMaterialLow;
        break;
	case EMaterialQuality::QUALITY_MEDIUM:
        cuttedProductCode.Quality = EProductMaterial::M2;
        timeByMaterial = timeByMaterialMidd;
        break;
	case EMaterialQuality::QUALITY_HIGH:
        cuttedProductCode.Quality = EProductMaterial::M3;
        timeByMaterial = timeByMaterialHigh;
        break;
    
    default:
        break;
    }

	switch (properties.Size)
    {
    case EMaterialSize::SIZE_SMALL:
        cuttedProductCode.Size = EProductSize::S1;
        timeBySize = timeBySizeLow;
        break;
	case EMaterialSize::SIZE_MEDIUM:
        cuttedProductCode.Size = EProductSize::S2;
        timeBySize = timeBySizeMidd;
        break;
	case EMaterialSize::SIZE_BIG:
        cuttedProductCode.Size = EProductSize::S3;
        timeBySize = timeBySizeHigh;
        break;
    
    default:
        break;
    }

	switch (properties.Length)
    {
    case EMaterialLength::LENGTH_SHORT:
        productsToProcess += 3;
        break;
	case EMaterialLength::LENGTH_MEDIUM:
        productsToProcess += 5;
        break;
	case EMaterialLength::LENGTH_LARGE:
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

    ACuttedProduct* cuttedProduct = GetWorld()->SpawnActor<ACuttedProduct>(productClass, spawnArrow->GetComponentLocation(), spawnArrow->GetComponentRotation());
    cuttedProduct->SetsProductProperties(productMeshToSpawn, productMaterialToSpawn, productSizeToSpawn);
    cuttedProduct->SetCuttedProductCode(productCode);
    productsToProcess --;

}