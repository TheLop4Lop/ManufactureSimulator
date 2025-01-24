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

        EMachineStatus NewStatus;
        (productsToProcess > 0)? NewStatus = EMachineStatus::ON_PRODUCTION : NewStatus = EMachineStatus::ON_HOLD;

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
                    wrongCodeOnEntrance.ExecuteIfBound(productOnEntrance->GetProductCode());
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
    switch (UEProductProperties::ConverStringToEnumQuality(properties.Left(2)))
    {
    case EPieceMaterial::QUALITY_LOW:
        molderedProductCode.Quality = EPieceMaterial::QUALITY_LOW;
        timeByMaterial = timeByMaterialLow;
        break;
	case EPieceMaterial::QUALITY_MEDIUM:
        molderedProductCode.Quality = EPieceMaterial::QUALITY_MEDIUM;
        timeByMaterial = timeByMaterialMidd;
        break;
	case EPieceMaterial::QUALITY_HIGH:
        molderedProductCode.Quality = EPieceMaterial::QUALITY_HIGH;
        timeByMaterial = timeByMaterialHigh;
        break;
    
    default:
        break;
    }

	switch (UEProductProperties::ConverStringToEnumSize(properties.Mid(2, 2)))
    {
    case EPieceSize::SIZE_SMALL:
        molderedProductCode.Size = EPieceSize::SIZE_SMALL;
        timeBySize = timeBySizeLow;
        break;
	case EPieceSize::SIZE_MEDIUM:
        molderedProductCode.Size = EPieceSize::SIZE_MEDIUM;
        timeBySize = timeBySizeMidd;
        break;
	case EPieceSize::SIZE_BIG:
        molderedProductCode.Size = EPieceSize::SIZE_BIG;
        timeBySize = timeBySizeHigh;
        break;
    
    default:
        break;
    }

	switch (UEProductProperties::ConverStringToEnumForm(codeToProcess.Right(2)))
    {
    case EPieceForm::FORM_CONE:
        molderedProductCode.Form = EPieceForm::FORM_CONE;
        timeByForm = timeByFormF1;
        break;
	case EPieceForm::FORM_CYLINDER:
        molderedProductCode.Form = EPieceForm::FORM_CYLINDER;
        timeByForm = timeByFormF2;
        break;
	case EPieceForm::FORM_TORUS:
        molderedProductCode.Form = EPieceForm::FORM_TORUS;
        timeByForm = timeByFormF3;
        break;

    default:
        break;
    }
    
    totalProductionPerPiece = timeByMaterial + timeBySize + timeByForm + oilPenalty;

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

        switch (molderedProductCode.Size)
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

        switch (molderedProductCode.Form)
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
	}

    if(productClass)
    {
        AMolderedProduct* molderedProduct = GetWorld()->SpawnActor<AMolderedProduct>(productClass, boxExit->GetComponentLocation(), boxExit->GetComponentRotation());
        molderedProduct->SetsProductProperties(productMeshToSpawn, productMaterialToSpawn, productSizeToSpawn);
        molderedProduct->SetProductCode(productCode);

        if(deleteIndex == productsQuality.Num() - 1 && productsQuality[deleteIndex] != 0)
        {
            molderedProduct->SetProductQuality(FMath::Max(0, productsQuality[deleteIndex] - lubricantPenalty));
            productsQuality[deleteIndex] = 0;
            deleteIndex = 0;
        }else if(productsQuality[deleteIndex] != 0)
        {
            molderedProduct->SetProductQuality(FMath::Max(0, productsQuality[deleteIndex] - lubricantPenalty));
            productsQuality[deleteIndex] = 0;
            deleteIndex++;
        }

        productsToProcess --;
    }

}
