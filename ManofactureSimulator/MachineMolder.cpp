// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineMolder.h"
#include "Components/BoxComponent.h"
#include "MolderedProduct.h"
#include "CuttedProduct.h"

///////////////////////////////////// STATUS PROPERTIES ////////////////////////////////
// Main varibles that controll the machine mechanic.

void AMachineMolder::SetPositionOfServiceDoor()
{
	FRotator doorRotation;
	(!isServiceDoorOpen)? doorRotation = FRotator(44.f, 303.0f, -108.0f) : doorRotation = FRotator(0.f, 0.f,0.f);
	machineServiceDoorMesh->SetRelativeRotation(doorRotation);

	isServiceDoorOpen = !isServiceDoorOpen;

}

//////////////////////////////////// PRODUCT PROCESS ////////////////////////////////
// Section for all the logic in process the product.

void AMachineMolder::CheckEntranceForProduct()
{
    if (boxEntrance)
    {
        TArray<AActor*> actorsOnEntrance;
        boxEntrance->GetOverlappingActors(actorsOnEntrance);

        EMachineStatus NewStatus = EMachineStatus::ON_PRODUCTION; // Default status

        for (AActor* singleActor : actorsOnEntrance)
        {
            if (singleActor && singleActor->IsA(classToTransform))
            {
                ACuttedProduct* productOnEntrance = Cast<ACuttedProduct>(singleActor);
                if (productOnEntrance->GetProductCode().Equals(codeToProcess.Left(4)))
                {
                    if (productOnEntrance && productsToProcess < maxProductOrder) // THIS CHANGE DEPENDING ON THE MACHINE
                    {
                        ManageCuttedProductProperties(productOnEntrance->GetProductCode());
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

// Gets the cuttedProduct properties and proces production product code.
void AMachineMolder::ManageCuttedProductProperties(FString properties)
{
    switch (GetStringToEnumMaterialMap(properties.Left(2)))
    {
    case EProductMaterial::M1:
        molderedProductCode.Quality = EProductMaterial::M1;
        timeByMaterial = timeByMaterialLow;
        break;
	case EProductMaterial::M2:
        molderedProductCode.Quality = EProductMaterial::M2;
        timeByMaterial = timeByMaterialMidd;
        break;
	case EProductMaterial::M3:
        molderedProductCode.Quality = EProductMaterial::M3;
        timeByMaterial = timeByMaterialHigh;
        break;
    
    default:
        break;
    }

	switch (GetStringToEnumSizeMap(properties.Mid(2, 2)))
    {
    case EProductSize::S1:
        molderedProductCode.Size = EProductSize::S1;
        timeBySize = timeBySizeLow;
        break;
	case EProductSize::S2:
        molderedProductCode.Size = EProductSize::S2;
        timeBySize = timeBySizeMidd;
        break;
	case EProductSize::S3:
        molderedProductCode.Size = EProductSize::S3;
        timeBySize = timeBySizeHigh;
        break;
    
    default:
        break;
    }

	switch (GetStringToEnumFormMap(codeToProcess.Right(2)))
    {
    case EProductForm::F1:
        molderedProductCode.Form = EProductForm::F1;
        timeByForm = timeByFormF1;
        break;
	case EProductForm::F2:
        molderedProductCode.Form = EProductForm::F2;
        timeByForm = timeByFormF2;
        break;
	case EProductForm::F3:
        molderedProductCode.Form = EProductForm::F3;
        timeByForm = timeByFormF3;
        break;

    default:
        break;
    }
    
    totalProductionPerPiece = timeByMaterial + timeBySize + timeByForm;

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
        switch (molderedProductCode.Quality)
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

        switch (molderedProductCode.Size)
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

        switch (molderedProductCode.Form)
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
	}

    if(productClass)
    {
        AMolderedProduct* molderedProduct = GetWorld()->SpawnActor<AMolderedProduct>(productClass, boxExit->GetComponentLocation(), boxExit->GetComponentRotation());
        molderedProduct->SetsProductProperties(productMeshToSpawn, productMaterialToSpawn, productSizeToSpawn);
        molderedProduct->SetProductCode(productCode);
        productsToProcess --;
    }

}
