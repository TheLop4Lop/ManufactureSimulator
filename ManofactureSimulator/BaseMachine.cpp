// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMachine.h"
#include "Components/PointLightComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "BaseConveyorBelt.h"
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

	computerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Computer Mesh"));
	computerMesh->SetupAttachment(machineMesh);

	boxEntrance = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Entrance"));
	boxEntrance->SetupAttachment(machineMesh);

	spawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Arrow"));
	spawnArrow->SetupAttachment(machineMesh);

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
	boxEntrance->GetOverlappingActors(initialActors);
	if(initialActors.IsValidIndex(0)) entranceConveyor = Cast<ABaseConveyorBelt>(initialActors[0]);	

}

// Called every frame
void ABaseMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetInitialMachineStatus();
	CheckEntranceForProduct();
	CheckConditionsForSpawnProduct();

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
				UE_LOG(LogTemp, Display, TEXT("YES"));
            	ABaseProduct* productOnEntrance = Cast<ABaseProduct>(singleActor); // THIS CHANGE DEPENDING ON THE MACHINE
				if(productOnEntrance && productsToProcess < maxProductOrder) // THIS CHANGE DEPENDING ON THE MACHINE
				{
					UE_LOG(LogTemp, Display, TEXT("PADENTRO"));
					ChangeProductionStatus(EMachineStatus::ON_PRODUCTION);
					productsToProcess++;

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

// Changes the production status light and actions.
void ABaseMachine::ChangeProductionStatus(EMachineStatus newStatus)
{
	switch (newStatus)
	{
	case EMachineStatus::ON_MAINTENANCE:
		machineStatusLight->SetLightColor(FColor::Blue);
		break;

	case EMachineStatus::ON_PRODUCTION:
		machineStatusLight->SetLightColor(FColor::Green);
		break;

	case EMachineStatus::ON_HOLD:
		machineStatusLight->SetLightColor(FColor::White);
		break;

	case EMachineStatus::FULL_PRODUCTION:
		machineStatusLight->SetLightColor(FColor::Orange);
		// PAUSE CONVEYOR BELT
		break;

	case EMachineStatus::PRODUCT_ERROR:
		machineStatusLight->SetLightColor(FColor::Red);
		// PAUSE CONVEYOR BELT
		break;

	case EMachineStatus::CODE_ERROR:
		machineStatusLight->SetLightColor(FColor::Yellow);
		// PAUSE CONVEYOR BELT
		break;
	
	default:
		break;
	}

}

void ABaseMachine::SetProductionMachineOrder(FString orderToProduce)
{
	codeToProcess = orderToProduce;

}

///////////////////////////////////// SPAWN PRODUCT ////////////////////////////////
// Section for spawn product and set properties.

// Checks all the conditions for spawn a product and spawn it.
void ABaseMachine::CheckConditionsForSpawnProduct()
{
	if(isPowered && isReady && isOnHold && !isInMaintenance && productsToProcess == 0)
	{
		// CONFIGURE PRODCUTION STATE LIGHT ON HOLD.
	}else if(isPowered && isReady && !isOnHold && !isInMaintenance && productsToProcess > 0 && !GetWorldTimerManager().IsTimerActive(spawnTimer))
	{
		// CONFIGURE PRODCUTION STATE LIGHT ON PRODUCTION.
		GetWorldTimerManager().SetTimer(spawnTimer, this, &ABaseMachine::SpawnProducedProduct, totalProductionPerPiece, true);
	}

}

// Spawn product based on a specific ABaseProduct child, dependes on the process and machine.
void ABaseMachine::SpawnProducedProduct()
{
	ABaseProduct* spawnProduct = GetWorld()->SpawnActor<ABaseProduct>(productClass, spawnArrow->GetComponentLocation(), spawnArrow->GetComponentRotation());
	if(productMesh.Num() > 0 && productSize.Num() > 0 && qualityMaterial.Num() > 0)
	{
		UE_LOG(LogTemp, Display, TEXT("SET Properties spawn properties in machine."));
		// DESIGN SET PROPERTIES ON SPAWNED PRODUCT. DEPENDS ON TYPE OF THE MACHINE.
	}
	productsToProcess --;

}
