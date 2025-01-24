// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMachine.h"
#include "Components/PointLightComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LubricantCanister.h"
#include "BaseConveyorBelt.h"
#include "OilCanister.h"
#include "BaseProduct.h"

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

}

// Called when the game starts or when spawned
void ABaseMachine::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> initialActors;
	productsQuality.SetNum(maxProductOrder);
	boxEntrance->GetOverlappingActors(initialActors);
	if(initialActors.IsValidIndex(0)) entranceConveyor = Cast<ABaseConveyorBelt>(initialActors[0]);

	SetInitialMachineStatus();

}

// Called every frame
void ABaseMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(isPowered)
	{
		SetPowerUpMachineStatus();
		CheckEntranceForProduct();	
		CheckConditionsForSpawnProduct();
		CheckForActorsInServiceBox();
	}else
	{
		SetPowerDownMachineStatus();
	}

}

///////////////////////////////////// MACHINE SOUND PROPERTIES ////////////////////////////////
// Section for all the machine sound properties.

// Manages production of Sound on machine mange status.
void ABaseMachine::ReproduceMachineSound(USoundBase* soundToReproduce)
{
	if(audioHandle && soundToReproduce)
	{
		audioHandle->Stop();
		audioHandle = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), soundToReproduce, GetActorLocation());
	}

}

///////////////////////////////////// STATUS PROPERTIES ////////////////////////////////
// Main varibles that controll the machine mechanic.

// Checks the conditions of machine at being gameplay.
void ABaseMachine::SetInitialMachineStatus()
{
	ChangeProductionStatus(EMachineStatus::OFF);
	isPowered = false;
	isReady = false;

}

// Checks the conditions of power machine and changes status for production.
void ABaseMachine::SetPowerUpMachineStatus()
{
	if(!isReady && !isInMaintenance && !GetWorldTimerManager().IsTimerActive(readySetUpTimer))
	{
		ChangeProductionStatus(EMachineStatus::ON_WARMING);
		GetWorldTimerManager().SetTimer(readySetUpTimer, this, &ABaseMachine::SetReadyMachineStatus, machineWarmUp, false);
		if(machineWarmUpSound)
		{
			audioHandle = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), machineWarmUpSound, GetActorLocation());
		}
	}

}

// Checks the conditions of to turn off machine.
void ABaseMachine::SetPowerDownMachineStatus()
{
	if(isReady && !GetWorldTimerManager().IsTimerActive(readySetUpTimer))
	{
		UE_LOG(LogTemp, Display, TEXT("SHOULD SHUT DOWN, CLEARING TIMERS"));
		GetWorldTimerManager().ClearTimer(processTimer); // Stops production timer.
		GetWorldTimerManager().SetTimer(readySetUpTimer, this, &ABaseMachine::ResetReadyMachineStatus, machineWarmDown, false);
		ReproduceMachineSound(machineTurnDownSound);
	}

}

// Sets ready status to true and clears timer.
void ABaseMachine::SetReadyMachineStatus()
{
	ChangeProductionStatus(EMachineStatus::ON_HOLD);
	UE_LOG(LogTemp, Display, TEXT("MACHINE ON AND READY!"));
	isReady = true;
	GetWorldTimerManager().ClearTimer(readySetUpTimer); // Resets ready timer.
	GetWorldTimerManager().ClearTimer(processTimer);

}

// Sets ready status to false and clears timer.
void ABaseMachine::ResetReadyMachineStatus()
{
	ChangeProductionStatus(EMachineStatus::OFF);
	UE_LOG(LogTemp, Display, TEXT("MACHINE OFF AND NOT READY!"));
	isReady = false;
	GetWorldTimerManager().ClearTimer(readySetUpTimer); // Resets ready timer.
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

// Called from Refueler computer after Widget Service Interaction; starts maintenance.
void ABaseMachine::StartMachineService()
{
	UE_LOG(LogTemp, Display, TEXT("RUNNING MAINTENANCE..."));
	isInMaintenance = true;
	ChangeProductionStatus(EMachineStatus::ON_MAINTENANCE);

	GetWorldTimerManager().ClearTimer(spawnTimer);
	GetWorldTimerManager().ClearTimer(processTimer);
	GetWorldTimerManager().SetTimer(processTimer, this, &ABaseMachine::RunMaintenance, maintenanceTime, false);

}

// Gets current Oil Level.
int ABaseMachine::GetOilLevel()
{
	return oilLevel;

}

// Gets MAX Oil Level.
int ABaseMachine::GetMaxOilLevel()
{
	return maxOilLevel;

}

// Gets current Lubricnt Level.
int ABaseMachine::GetLubricantLevel()
{
	return lubricantLevel;

}

// Gets MAX Lubricant Level.
int ABaseMachine::GetMaxLubricantLevel()
{
	return maxLubricantLevel;

}

FColor ABaseMachine::GetMachineStatusColor()
{
	return machineStatusColor;

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
					if(productsToProcess > 0) ChangeProductionStatus(EMachineStatus::ON_PRODUCTION);
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
	case EMachineStatus::ON_WARMING:
		// Sound being initiated on SetPowerUpMachineStatus().
		bProductionOnPlaying = false;

		machineStatusLight->SetIntensity(2500.0f);
		machineStatusLight->SetLightColor(FColor::White);
		conveyorEvent.ExecuteIfBound(machineName, false);
		machineStatusColor = FColor::White;
		break;
	
	case EMachineStatus::ON_MAINTENANCE:
		ReproduceMachineSound(serviceSound);
		bProductionOnPlaying = false;

		machineStatusLight->SetIntensity(2500.0f);
		machineStatusLight->SetLightColor(FColor::Blue);
		conveyorEvent.ExecuteIfBound(machineName, false);
		machineStatusColor = FColor::Blue;
		break;

	case EMachineStatus::ON_PRODUCTION:
		if(!bProductionOnPlaying) ReproduceMachineSound(machineProductionSound);
		bProductionOnPlaying = true;

		UE_LOG(LogTemp, Warning, TEXT("Machine: %s, Changing status to ON_PRODUCTION"), *GetActorLabel());
		machineStatusLight->SetIntensity(2500.0f);
		machineStatusLight->SetLightColor(FColor::Green);
		conveyorEvent.ExecuteIfBound(machineName, true);
		machineStatusColor = FColor::Green;
		break;

	case EMachineStatus::ON_HOLD:
		ReproduceMachineSound(machineOnSound);
		bProductionOnPlaying = false;

		UE_LOG(LogTemp, Warning, TEXT("Machine: %s, Changing status to ON_HOLD"), *GetActorLabel());
		machineStatusLight->SetIntensity(2500.0f);
		machineStatusLight->SetLightColor(FColor::Yellow);
		conveyorEvent.ExecuteIfBound(machineName, true);
		machineStatusColor = FColor::Yellow;
		break;

	case EMachineStatus::FULL_PRODUCTION:
		UE_LOG(LogTemp, Warning, TEXT("Machine: %s, Changing status to FULL_PRODUCTION"), *GetActorLabel());
		machineStatusLight->SetIntensity(2500.0f);
		machineStatusLight->SetLightColor(FColor::Turquoise);
		conveyorEvent.ExecuteIfBound(machineName, false);
		machineStatusColor = FColor::Turquoise;
		break;

	case EMachineStatus::PRODUCT_ERROR:
		if(pieceErrorSound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), pieceErrorSound, GetActorLocation());
		ReproduceMachineSound(machineOnSound);
		bProductionOnPlaying = false;

		UE_LOG(LogTemp, Warning, TEXT("Machine: %s, Changing status to PRODUCT_ERROR"), *GetActorLabel());
		machineStatusLight->SetIntensity(2500.0f);
		machineStatusLight->SetLightColor(FColor::Red);
		conveyorEvent.ExecuteIfBound(machineName, false);
		machineStatusColor = FColor::Red;
		break;

	case EMachineStatus::CODE_ERROR:
		if(codeErrorSound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), codeErrorSound, GetActorLocation());
		ReproduceMachineSound(machineOnSound);
		bProductionOnPlaying = false;

		UE_LOG(LogTemp, Warning, TEXT("Machine: %s, Changing status to CODE_ERROR"), *GetActorLabel());
		machineStatusLight->SetIntensity(2500.0f);
		machineStatusLight->SetLightColor(FColor::Orange);
		conveyorEvent.ExecuteIfBound(machineName, false);
		machineStatusColor = FColor::Orange;
		break;

	case EMachineStatus::OFF:
		bProductionOnPlaying = false;

		UE_LOG(LogTemp, Warning, TEXT("Machine: %s, Machine OFF"), *GetActorLabel());
		machineStatusLight->SetIntensity(0.0f);
		conveyorEvent.ExecuteIfBound(machineName, false);
		machineStatusColor = FColor::Black;
		break;
	
	default:
		break;
	}

}

// Called frm Refueler Computer after widget Power interactio; change status between ON and OFF.
void ABaseMachine::SetMachinePower()
{
	if(!GetWorldTimerManager().IsTimerActive(readySetUpTimer))
	{
		isPowered = !isPowered;
		UE_LOG(LogTemp, Display, TEXT("CHANGIN POWER: %s"), isPowered? TEXT("ON") : TEXT("OFF"));
	}

}

// Returns Computer Status for Widget interaction light.
bool ABaseMachine::GetMachinePower()
{
	return isPowered;

}

// Sets value of order code for the machinery to process from machine computer.
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
    }
}

// Reduces the lubricant in the machine, this affects the quality of the product.
void ABaseMachine::ReduceLubricantLevel()
{
    if (lubricantLevel > 0)
    {
        lubricantLevel = (lubricantLevel < 40) ? FMath::Max(0, lubricantLevel - 2) : FMath::Max(0, lubricantLevel - 1);
		UpdateLubricantPenalty();
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
		oilPenalty = 5.0f;
	}else
	{
		oilPenalty = 9.0f;
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
			UE_LOG(LogTemp, Display, TEXT("EMPTY"));
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
		if(singleActor->IsA(AOilCanister::StaticClass()) && !GetWorldTimerManager().IsTimerActive(FillUpTankTimer) && !isInMaintenance)
		{
			oilCanister = Cast<AOilCanister>(singleActor);
			GetWorldTimerManager().SetTimer(FillUpTankTimer, this, &ABaseMachine::FillUpOilTank, fillUpTime, true);
			DoOnceService = true;
		}else if(singleActor->IsA(ALubricantCanister::StaticClass()) && !GetWorldTimerManager().IsTimerActive(FillUpTankTimer) && !isInMaintenance)
		{
			lubricantCanister = Cast<ALubricantCanister>(singleActor);
			GetWorldTimerManager().SetTimer(FillUpTankTimer, this, &ABaseMachine::FillUpLubricantTan, fillUpTime, true);
			DoOnceService = true;
		}
	}

}

// Method called by Timer, set Service configuration for machine maintinance.
void ABaseMachine::RunMaintenance()
{
	if(!prevOilLevel == 0)
	{
		oilLevel += prevOilLevel;
		prevOilLevel = 0;
	}

	if(!prevLubricantLevel == 0)
	{
		lubricantLevel += prevLubricantLevel;
		prevLubricantLevel = 0;
	}

	isInMaintenance = false;
	ChangeProductionStatus(EMachineStatus::ON_HOLD);
	GetWorldTimerManager().SetTimer(spawnTimer, this, &ABaseMachine::TryToSpawnProduct, totalProductionPerPiece, true);
	UE_LOG(LogTemp, Display, TEXT("MAINTENANCE DONE!"));
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
	}
	else if(isReady && !isOnHold && !isInMaintenance)
	{
		if (lastProductionTime != totalProductionPerPiece)
		{
			UE_LOG(LogTemp, Error, TEXT("Machine: %s, Reset to Time: %f"), *GetActorLabel(), totalProductionPerPiece);
			GetWorldTimerManager().ClearTimer(spawnTimer);
			GetWorldTimerManager().SetTimer(spawnTimer, this, &ABaseMachine::TryToSpawnProduct,
				totalProductionPerPiece, true);

			lastProductionTime = totalProductionPerPiece;
		}
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
		// DESIGN SET PROPERTIES ON SPAWNED PRODUCT. DEPENDS ON TYPE OF THE MACHINE.
	}

	if(deleteIndex == productsQuality.Num() - 1 && productsQuality[deleteIndex] != 0) // Quality based on Lubrican level implemented on Child Classes.
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
