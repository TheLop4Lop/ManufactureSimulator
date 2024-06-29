// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineMolder.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "MolderedProduct.h"
#include "CuttedProduct.h"

//////////////////////////////////// PRODUCT PROCESS ////////////////////////////////
// Section for all the logic in process the product.

// Checks the actors on the boxEntrance, this will change depending on the machine.
void AMachineMolder::CheckEntranceForProduct()
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
            	ACuttedProduct* productOnEntrance = Cast<ACuttedProduct>(singleActor);
				if((productOnEntrance && productsToProcess < maxProductOrder)) // THIS CHANGE DEPENDING ON THE MACHINE
				{
					UE_LOG(LogTemp, Display, TEXT("PADENTRO"));
                    ManageCuttedProductProperties(GetMolderedProductCode(productOnEntrance->GetCuttedProductCode()));
					ChangeProductionStatus(EMachineStatus::ON_PRODUCTION);

					//productOnEntrance->DestroyProduct();
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

// Gets the cuttedProduct properties and proces production product code.
void AMachineMolder::ManageCuttedProductProperties(FProductForm properties)
{
    switch (properties.Quality)
    {
    case EProductMaterial::M1:
        timeByMaterial = timeByMaterialLow;
        break;
	case EProductMaterial::M2:
        timeByMaterial = timeByMaterialMidd;
        break;
	case EProductMaterial::M3:
        timeByMaterial = timeByMaterialHigh;
        break;
    
    default:
        break;
    }

	switch (properties.Size)
    {
    case EProductSize::S1:
        timeBySize = timeBySizeLow;
        break;
	case EProductSize::S2:
        timeBySize = timeBySizeMidd;
        break;
	case EProductSize::S3:
        timeBySize = timeBySizeHigh;
        break;

    default:
        break;
    }

    switch (properties.Form)
    {
    case EProductForm::F1:
        timeByForm = timeByFormF1;
        break;
	case EProductForm::F2:
        timeByForm = timeByFormF2;
        break;
	case EProductForm::F3:
        timeByForm = timeByFormF3;
        break;

    default:
        break;
    }

    totalProductionPerPiece = timeByMaterial + timeBySize + timeByForm;

}

FProductForm& AMachineMolder::GetMolderedProductCode(FString& cuttedProductCode)
{
    molderedProductCode.Quality = GetStringToEnumMaterialMap(cuttedProductCode.Left(2));
    molderedProductCode.Size = GetStringToEnumSizeMap(cuttedProductCode.Right(2));

    //molderedProductCode.Form = GetStringToEnumFormMap(VALUE FROM COMPUTER, IMPLEMENT IT);

    return molderedProductCode;
}

///////////////////////////////////// SPAWN PRODUCT ////////////////////////////////
// Section for spawn product and set properties.

// Spawn product based on a specific ABaseProduct child, dependes on the process and machine.
void AMachineMolder::SpawnProducedProduct()
{  
    UStaticMesh* productMeshToSpawn = nullptr;
    FVector productSizeToSpawn = FVector::ZeroVector;
    UMaterial* productMaterialToSpawn = nullptr;
    FString productCode = "";
    
    if(productMesh.Num() > 0 && productSize.Num() > 2 && qualityMaterial.Num() > 2)
	{
        productMeshToSpawn = productMesh[0];
		switch (molderedProductCode.Quality)
        {
        case EProductMaterial::M1:
            productMaterialToSpawn = qualityMaterial[0];
            break;
        
        case EProductMaterial::M2:
            productMaterialToSpawn = qualityMaterial[1];
            break;

        case EProductMaterial::M3:
            productMaterialToSpawn = qualityMaterial[2];
            break;

        default:
            break;
        }

        switch (molderedProductCode.Size)
        {
        case EProductSize::S1:
            productSizeToSpawn = productSize[0];
            break;
        
        case EProductSize::S2:
            productSizeToSpawn = productSize[1];
            break;

        case EProductSize::S3:
            productSizeToSpawn = productSize[2];
            break;

        default:
            break;
        }
	}

    AMolderedProduct* cuttedProduct = GetWorld()->SpawnActor<AMolderedProduct>(productClass, spawnArrow->GetComponentLocation(), spawnArrow->GetComponentRotation());
    cuttedProduct->SetsProductProperties(productMeshToSpawn, productMaterialToSpawn, productSizeToSpawn);
    productsToProcess --;

}
