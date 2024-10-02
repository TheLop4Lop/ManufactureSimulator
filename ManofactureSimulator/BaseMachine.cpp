// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMachine.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"
#include "LubricantCanister.h"
#include "BaseConveyorBelt.h"
#include "OilCanister.h"
#include "BaseProduct.h"

// Static MATERIAL map for string to ENUM data, this is used for product interpretation in respective machine.
std::map<FString, EProductMaterial> ABaseMachine::StringToEnumMaterialMap;

// Static SIZE map for string to ENUM data, this is used for product interpretation in respective machine.
std::map<FString, EProductSize> ABaseMachine::StringToEnumSizeMap;

// Static LENGTH map for string to ENUM data, this is used for product interpretation in respective machine.
std::map<FString, EProductLength> ABaseMachine::StringToEnumLengthMap;

// Static FORM map for string to ENUM data, this is used for product interpretation in respective machine.
std::map<FString, EProductForm> ABaseMachine::StringToEnumFormMap;

// Static COLOR map for string to ENUM data, this is used for product interpretation in respective machine.
std::map<FString, EProductColor> ABaseMachine::StringToEnumColorMap;

// Sets default values
ABaseMachine::ABaseMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	machineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Machine Mesh"));
	RootComponent = machineMesh;

	productDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Product Door Mesh"));
	productDoorMesh->SetupAttachment(machineMesh);

	machineServiceDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Machine Door Mesh"));
	machineServiceDoorMesh->SetupAttachment(machineMesh);

	machineActionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Machine Action Mesh"));
	machineActionMesh->SetupAttachment(machineMesh);

	boxEntrance = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Entrance"));
	boxEntrance->SetupAttachment(machineMesh);

	boxExit = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Exit"));
	boxExit->SetupAttachment(machineMesh);

	boxService = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Maintenance"));
	boxService->SetupAttachment(machineMesh);

	machineStatusLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Machine Status Light"));
	machineStatusLight->SetupAttachment(machineMesh);

	if(StringToEnumMaterialMap.empty() && StringToEnumSizeMap.empty() && StringToEnumFormMap.empty() && StringToEnumColorMap.empty())
	{
		InitializeConversionMaps();
	}

}

// Called when the game starts or when spawned
void ABaseMachine::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> initialActors;
	productsQuality.SetNum(maxProductOrder);
	boxEntrance->GetOverlappingActors(initialActors);
	if(initialActors.IsValidIndex(0)) entranceConveyor = Cast<ABaseConveyorBelt>(initialActors[0]);

}

// Called every frame
void ABaseMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(isPowered)
	{
		SetInitialMachineStatus();
		CheckEntranceForProduct();	
		CheckConditionsForSpawnProduct();
		CheckForActorsInServiceBox();
	}else
	{
		ChangeProductionStatus(EMachineStatus::OFF);
	}

}

///////////////////////////////////// MAP CONVERTION ////////////////////////////////
// Singleton implementation for String-ENUM convertion, this help to all child classes access to transformation.

void ABaseMachine::InitializeConversionMaps()
{
	StringToEnumMaterialMap = {{"M1", EProductMaterial::M1}, {"M2", EProductMaterial::M2}, {"M3", EProductMaterial::M3}};

	StringToEnumSizeMap = {{"S1", EProductSize::S1}, {"S2", EProductSize::S2}, {"S3", EProductSize::S3}};

	StringToEnumLengthMap = {{"L1", EProductLength::L1}, {"L2", EProductLength::L2}, {"L3", EProductLength::L3}};

	StringToEnumFormMap = {{"F1", EProductForm::F1}, {"F2", EProductForm::F2}, {"F3", EProductForm::F3}};

	StringToEnumColorMap = {{"C1", EProductColor::C1}, {"C2", EProductColor::C2}, {"C3", EProductColor::C3}};

}

// Gets the StringToEnumMaterialMap
EProductMaterial ABaseMachine::GetStringToEnumMaterialMap(const FString& materialString) const
{
	auto it = StringToEnumMaterialMap.find(materialString);
	if(it != StringToEnumMaterialMap.end())
	{
		return it->second;
	}

	return EProductMaterial::M1;

}

// Gets the StringToEnumSizeMap
EProductSize ABaseMachine::GetStringToEnumSizeMap(const FString& sizeString) const
{
	auto it = StringToEnumSizeMap.find(sizeString);
	if(it != StringToEnumSizeMap.end())
	{
		return it->second;
	}

	return EProductSize::S1;

}

// Gets the StringToEnumLengthMap
EProductLength ABaseMachine::GetStringToEnumLengthMap(const FString& lengthString) const
{
	auto it = StringToEnumLengthMap.find(lengthString);
	if(it != StringToEnumLengthMap.end())
	{
		return it->second;
	}

	return EProductLength::L1;

}

// Gets the StringToEnumFormMap
EProductForm ABaseMachine::GetStringToEnumFormMap(const FString& formString) const
{
	auto it = StringToEnumFormMap.find(formString);
	if(it != StringToEnumFormMap.end())
	{
		return it->second;
	}

	return EProductForm::F1;

}

// Gets the StringToEnumColorMap
EProductColor ABaseMachine::GetStringToEnumColorMap(const FString& colorString) const
{
	auto it = StringToEnumColorMap.find(colorString);
	if(it != StringToEnumColorMap.end())
	{
		return it->second;
	}

	return EProductColor::C1;

}

///////////////////////////////////// STATUS PROPERTIES ////////////////////////////////
// Main varibles that controll the machine mechanic.

// Checks the conditions of power machine and changes status for production.
void ABaseMachine::SetInitialMachineStatus()
{
	if(isPowered && !isReady && !isInMaintenance && !GetWorldTimerManager().IsTimerActive(processTimer))
	{
		// CONFIGURE PRODCUTION STATE LIGHT ON WARMING.
		GetWorldTimerManager().SetTimer(processTimer, this, &ABaseMachine::SetReadyMachineStatus, machineWarmUp, false);
	}else if(!isPowered && isReady && !GetWorldTimerManager().IsTimerActive(processTimer))
	{
		// CONFIGURE PRODCUTION STATE LIGHT OFF.
		GetWorldTimerManager().SetTimer(processTimer, this, &ABaseMachine::ResetReadyMachineStatus, machineWarmDown, false);
	}

}

// Sets ready status to true and clears timer.
void ABaseMachine::SetReadyMachineStatus()
{
	isReady = true;
	GetWorldTimerManager().ClearTimer(processTimer);

}

// Sets ready status to false and clears timer.
void ABaseMachine::ResetReadyMachineStatus()
{
	isReady = false;
	GetWorldTimerManager().ClearTimer(processTimer);
}

// Sets the position and status of product door.
void ABaseMachine::SetPositionOfProductDoor()
{
	FRotator doorRotation;
	(!isProductDoorOpen)? doorRotation = FRotator(0.f, 0.f, -90.f) : doorRotation = FRotator(0.f, 0.f,0.f);
	productDoorMesh->SetRelativeRotation(doorRotation);

	isProductDoorOpen = !isProductDoorOpen;

}

void ABaseMachine::SetPositionOfServiceDoor()
{
	FRotator doorRotation;
	(!isServiceDoorOpen)? doorRotation = FRotator(0.f, 0.f, -100.f) : doorRotation = FRotator(0.f, 0.f,0.f);
	machineServiceDoorMesh->SetRelativeRotation(doorRotation);

	isServiceDoorOpen = !isServiceDoorOpen;

}

///////////////////////////////////// PRODUCT PROCESS ////////////////////////////////
// Section for all the logic in process the product.

// Checks the actors on the boxEntrance, this will change depending on the machine.
void ABaseMachine::CheckEntranceForProduct()
{
	if (boxEntrance)
	{
		TArray<AActor*> actorsOnEntrance;
   		boxEntrance->GetOverlappingActors(actorsOnEntrance);

    	for (AActor* singleActor : actorsOnEntrance)
    	{
        	if (singleActor && singleActor->IsA(classToTransform))
        	{
            	ABaseProduct* productOnEntrance = Cast<ABaseProduct>(singleActor); // THIS CHANGE DEPENDING ON THE MACHINE
				if(productOnEntrance && productsToProcess < maxProductOrder) // THIS CHANGE DEPENDING ON THE MACHINE
				{
					ChangeProductionStatus(EMachineStatus::ON_PRODUCTION);
					productsToProcess++;

					InsertQualityToArray(productOnEntrance->GetProductQuality());
					productOnEntrance->DestroyProduct();
				}else
				{
					ChangeProductionStatus(EMachineStatus::FULL_PRODUCTION);
				}
        	}else
			{
				ChangeProductionStatus(EMachineStatus::CODE_ERROR);
			}
    	}
	}

}

// Changes the production status light and actions.
void ABaseMachine::ChangeProductionStatus(EMachineStatus newStatus)
{
	switch (newStatus)
	{
	case EMachineStatus::ON_MAINTENANCE:
		machineStatusLight->SetLightColor(FColor::Blue);
		conveyorEvent.ExecuteIfBound(machineName, false);
		break;

	case EMachineStatus::ON_PRODUCTION:
		UE_LOG(LogTemp, Warning, TEXT("Changing status to ON_PRODUCTION"));
		machineStatusLight->SetLightColor(FColor::Green);
		conveyorEvent.ExecuteIfBound(machineName, true);
		break;

	case EMachineStatus::ON_HOLD:
		UE_LOG(LogTemp, Warning, TEXT("Changing status to ON_HOLD"));
		machineStatusLight->SetLightColor(FColor::White);
		conveyorEvent.ExecuteIfBound(machineName, true);
		break;

	case EMachineStatus::FULL_PRODUCTION:
		UE_LOG(LogTemp, Warning, TEXT("Changing status to FULL_PRODUCTION"));
		machineStatusLight->SetLightColor(FColor::Orange);
		conveyorEvent.ExecuteIfBound(machineName, false);
		break;

	case EMachineStatus::PRODUCT_ERROR:
		UE_LOG(LogTemp, Warning, TEXT("Changing status to PRODUCT_ERROR"));
		machineStatusLight->SetLightColor(FColor::Red);
		conveyorEvent.ExecuteIfBound(machineName, false);
		break;

	case EMachineStatus::CODE_ERROR:
		UE_LOG(LogTemp, Warning, TEXT("Changing status to CODE_ERROR"));
		machineStatusLight->SetLightColor(FColor::Yellow);
		conveyorEvent.ExecuteIfBound(machineName, false);
		break;

	case EMachineStatus::OFF:
		UE_LOG(LogTemp, Warning, TEXT("Machine OFF"));
		machineStatusLight->SetIntensity(0.0f);
		conveyorEvent.ExecuteIfBound(machineName, false);
		break;
	
	default:
		break;
	}

}

void ABaseMachine::SetProductionMachineOrder(FString orderToProduce)
{
	codeToProcess = orderToProduce;
	UE_LOG(LogTemp, Display, TEXT("codeToProcess: %s"), *codeToProcess);
}

bool ABaseMachine::CheckClearExit()
{
	TArray<AActor*> overlappingActors;
	boxExit->GetOverlappingActors(overlappingActors);
	if(overlappingActors.Num() != 0)
	{
		return false;
	}

	return true;

}

///////////////////////////////////// PRODUCT QUALITY PROCESS ////////////////////////////////
// Section for all the logic of quality product process.

// Checks and store quality values from pieces into the productsQuality array.
void ABaseMachine::InsertQualityToArray(int pieceQuality)
{
	if(insertIndex == productsQuality.Num() - 1 && productsQuality[insertIndex] == 0)
	{
		productsQuality[insertIndex] = pieceQuality;
		insertIndex = 0;
	}else if(productsQuality[insertIndex] == 0)
	{
		productsQuality[insertIndex] = pieceQuality;
		insertIndex++;
	}

}

// Reduces the oil in the machine, this affects production time.
void ABaseMachine::ReduceOilLevel()
{
    if (oilLevel > 0)
    {
        oilLevel = (oilLevel < 40) ? FMath::Max(0, oilLevel - 2) : FMath::Max(0, oilLevel - 1);
		UpdateOilPenalty();

		UE_LOG(LogTemp, Warning, TEXT("MACHINE REPORT: %s, OIL LEVEL: %i, PENALTY: %f"), *GetActorLabel(), oilLevel, oilPenalty);
    }
}

// Reduces the lubricant in the machine, this affects the quality of the product.
void ABaseMachine::ReduceLubricantLevel()
{
    if (lubricantLevel > 0)
    {
        lubricantLevel = (lubricantLevel < 40) ? FMath::Max(0, lubricantLevel - 3) : FMath::Max(0, lubricantLevel - 1);
		UpdateLubricantPenalty();

		UE_LOG(LogTemp, Warning, TEXT("MACHINE REPORT: %s, LUBRICANT LEVEL: %i, PENALTY: %i"), *GetActorLabel(), lubricantLevel, lubricantPenalty);
    }
}

// Updates the penalty based on oilLevel.
void ABaseMachine::UpdateOilPenalty()
{
	if(oilLevel > 80)
	{
		oilPenalty = 0.0f;
	}else if(oilLevel > 60)
	{
		oilPenalty = 1.0f;
	}else if(oilLevel > 40)
	{
		oilPenalty = 2.0f;
	}else if(oilLevel > 20)
	{
		oilPenalty = 3.0f;
	}else
	{
		oilPenalty = 5.0f;
	}

}

// Updates the lubricant penalty based on lubricantLevel.
void ABaseMachine::UpdateLubricantPenalty()
{
	if(lubricantLevel > 80)
	{
		lubricantPenalty = 0;
	}else if(lubricantLevel > 60)
	{
		lubricantPenalty = 5;
	}else if(lubricantLevel > 40)
	{
		lubricantPenalty = 10;
	}else if(lubricantLevel > 20)
	{
		lubricantPenalty = 30;
	}else
	{
		lubricantPenalty = 60;
	}

}

///////////////////////////////////// SERVICE PROCESS ////////////////////////////////
// Section for all the logic of MAINTENANCE PPROCESS.

// Method called by timer. Restores oil quantity by canister collision.
void ABaseMachine::FillUpOilTank()
{
	if(oilCanister)
	{
		if(oilCanister->GetCanisterCurrentLevel() > 0)
		{
			UE_LOG(LogTemp, Display, TEXT("FILLING OIL IN THE MACHINE."));
			int missingOilLevel = maxOilLevel - oilLevel;
			if(prevOilLevel < missingOilLevel)
			{
				prevOilLevel++;
				oilCanister->ReduceCanister();
			}
		}
	}

}

// Method called by timer. Restores lubricant quantity by canister collision.
void ABaseMachine::FillUpLubricantTan()
{
	if(lubricantCanister)
	{
		if(lubricantCanister->GetCanisterCurrentLevel() > 0)
		{
			UE_LOG(LogTemp, Display, TEXT("FILLING LUBRICANT IN THE MACHINE"));
			int missingLubricantLevel = maxLubricantLevel - lubricantLevel;
			if(prevLubricantLevel < missingLubricantLevel)
			{
				prevLubricantLevel++;
				lubricantCanister->ReduceCanister();
			}
		}
	}

}

// Logic for detect actors in box Service when Service Door is Open.
void ABaseMachine::CheckForActorsInServiceBox()
{
	if(isServiceDoorOpen)
	{
		GetWorldTimerManager().SetTimer(serviceDoorTimer, this, &ABaseMachine::CloseUpServiceDoorByTimer, closeServiceDoorTime, false);

		TArray<AActor*> actorsInServiceDoor;
		boxService->GetOverlappingActors(actorsInServiceDoor);

		if(actorsInServiceDoor.Num() == 0 && DoOnceService)
		{
			UE_LOG(LogTemp, Display, TEXT("EMMMMMMMMMMMMPTY"));
			ClearCanisterTimers();
		}

		if(actorsInServiceDoor.Num() > 0)
		{
			bool canisterFound = false;
			CheckActorsForCanisterClass(actorsInServiceDoor, canisterFound);
			if(canisterFound)
			{
				CheckTypeOfCanister(actorsInServiceDoor);
			}
		}
	}

}

// Method to clear canister references and FillUpTankTimer.
void ABaseMachine::ClearCanisterTimers()
{
	GetWorldTimerManager().ClearTimer(FillUpTankTimer);
	oilCanister = nullptr;
	lubricantCanister = nullptr;

	DoOnceService = false;

}

// Check actors in service box to know if any is a ABaseCanister class.
void ABaseMachine::CheckActorsForCanisterClass(const TArray<AActor*>& actorsBox, bool& canisterFound)
{
	for(AActor* singleActor : actorsBox)
	{
		if(singleActor->IsA(ABaseCanister::StaticClass()))
		{
			canisterFound = true;
			break;
		}else
		{
			UE_LOG(LogTemp, Display, TEXT("NO CANISTER"));
			canisterFound = false;
		}
	}

}

// Checks type of canister in the service box.
void ABaseMachine::CheckTypeOfCanister(const TArray<AActor*>& actorsBox)
{
	for(AActor* singleActor : actorsBox)
	{
		if(singleActor->IsA(AOilCanister::StaticClass()) && !GetWorldTimerManager().IsTimerActive(FillUpTankTimer))
		{
			oilCanister = Cast<AOilCanister>(singleActor);
			GetWorldTimerManager().SetTimer(FillUpTankTimer, this, &ABaseMachine::FillUpOilTank, fillUpTime, true);
			DoOnceService = true;
		}else if(singleActor->IsA(ALubricantCanister::StaticClass()) && !GetWorldTimerManager().IsTimerActive(FillUpTankTimer))
		{
			lubricantCanister = Cast<ALubricantCanister>(singleActor);
			GetWorldTimerManager().SetTimer(FillUpTankTimer, this, &ABaseMachine::FillUpLubricantTan, fillUpTime, true);
			DoOnceService = true;
		}
	}

}

// Checks if isServiceDoorOpen is true, if it is, calls SetPositionOfServiceDoor to close door. This to prevent continuos check in tick.
void ABaseMachine::CloseUpServiceDoorByTimer()
{
	if(isServiceDoorOpen)
	{
		SetPositionOfServiceDoor();
	}

	GetWorldTimerManager().ClearTimer(serviceDoorTimer);

}

///////////////////////////////////// SPAWN PRODUCT ////////////////////////////////
// Section for spawn product and set properties.

// Checks all the conditions for spawn a product and spawn it.
void ABaseMachine::CheckConditionsForSpawnProduct()
{
	if(isReady && isOnHold && !isInMaintenance)
	{
		ChangeProductionStatus(EMachineStatus::ON_HOLD);
	}else if(isReady && !isOnHold && !isInMaintenance && !GetWorldTimerManager().IsTimerActive(spawnTimer))
	{
		GetWorldTimerManager().SetTimer(spawnTimer, this, &ABaseMachine::TryToSpawnProduct, 
			totalProductionPerPiece + oilPenalty, true);
	}

}

// Is a callback function by a timer, first check is exit is clear, then spawn product.
void ABaseMachine::TryToSpawnProduct()
{
	if(CheckClearExit() && (productsToProcess > 0))
	{
		SpawnProducedProduct();
		productsProduced++;
		if(productsProduced % oilReductionByPiece == 0)
		{
			ReduceOilLevel();
		}

		if(productsProduced % lubricantReductionByOil == 0)
		{
			ReduceLubricantLevel();
		}
	}

}

// Spawn product based on a specific ABaseProduct child, dependes on the process and machine.
void ABaseMachine::SpawnProducedProduct()
{
	ABaseProduct* spawnProduct = GetWorld()->SpawnActor<ABaseProduct>(productClass, boxExit->GetComponentLocation(), boxExit->GetComponentRotation());
	if(productMesh.Num() > 0 && productSize.Num() > 0 && qualityMaterial.Num() > 0)
	{
		UE_LOG(LogTemp, Display, TEXT("SET Properties spawn properties in machine."));
		// DESIGN SET PROPERTIES ON SPAWNED PRODUCT. DEPENDS ON TYPE OF THE MACHINE.
	}

	if(deleteIndex == productsQuality.Num() - 1 && productsQuality[deleteIndex] != 0)
	{
		spawnProduct->SetProductQuality(productsQuality[deleteIndex]);
		productsQuality[deleteIndex] = 0;
		deleteIndex = 0;
	}else if(deleteIndex == productsQuality.Num() - 1)
	{
		deleteIndex = 0;
		spawnProduct->SetProductQuality(productsQuality[deleteIndex]);
	}else if(productsQuality[deleteIndex] != 0)
	{
		spawnProduct->SetProductQuality(productsQuality[deleteIndex]);
		deleteIndex++;
	}
	
	productsToProcess --;

}
