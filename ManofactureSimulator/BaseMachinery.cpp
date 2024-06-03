// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMachinery.h"
#include "Components/SpotLightComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MachineComputerWidget.h"
#include "PieceSpawnProperties.h"
#include "CharacterController.h"
#include "BaseConveyorBelt.h"
#include "Piece.h"
#include <string>
#include <map>

// Sets default values
ABaseMachinery::ABaseMachinery()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	MachineComputerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Computer Mesh"));
	MachineComputerMesh->SetupAttachment(StaticMesh);

	BoxEntrance = CreateDefaultSubobject<UBoxComponent>(TEXT("Machine Entrance"));
	BoxEntrance->SetupAttachment(StaticMesh);

	BoxExit = CreateDefaultSubobject<UBoxComponent>(TEXT("Machine Exit"));
	BoxExit->SetupAttachment(StaticMesh);

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spot Light"));
	SpotLight->SetupAttachment(StaticMesh);

}

// Called when the game starts or when spawned
void ABaseMachinery::BeginPlay()
{
	Super::BeginPlay();

	Properties = FindComponentByClass<UPieceSpawnProperties>();
	FindConveyorBelt();

	bDoOnceStopConveyort = true;

	FVector TemporaryVector = BoxExit->GetRelativeLocation();
	FTransform ComponentTransform = BoxExit->GetOwner()->GetTransform();
	FVector WorldLocation = ComponentTransform.TransformPosition(TemporaryVector);

	SpawnProductLocation = WorldLocation;
	StopConveyorBelt();
	SpotLight->SetIntensity(0);

}

// Called every frame
void ABaseMachinery::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsPowered)
	{
		HandleRawPiecesProduction();
		RawPieceEntranceManager();

		if(SpotLight != nullptr)
		{
			SpotLight->SetIntensity(1600);
			SpotLight->SetLightColor(ColorCode);
		}
	}

	if(bInMaintenance && DoOnceMantenance)
	{
		HandleMaintenanceMode();
		DoOnceMantenance = false;
	}

	if(ComputerWidget != nullptr)
	{
		ComputerWidget->SetWrongOrderName(SetProductionOrderName(HoldPieceIndex));

		if(bInMaintenance)
		{
			MaintenanceHoldSeconds += (GetWorld()->GetDeltaSeconds())/MaintenanceTimeHold;
			ComputerWidget->SetMaintenanceBarProgress(MaintenanceHoldSeconds);
		}else/////Problem with the maintenance button, it works when power is off
		{
			MaintenanceHoldSeconds = 0;
			ComputerWidget->SetMaintenanceBarProgress(MaintenanceHoldSeconds);
		}
	}

}

// Called to bind functionality to input
void ABaseMachinery::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseMachinery::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	ComputerWidget = Cast<UMachineComputerWidget>(CreateWidget(CharacterController, ComputerClass));
	ComputerWidget->SetBaseMachineComputer(this);
	ComputerWidget->AddToViewport();

}

void ABaseMachinery::FindConveyorBelt()
{
	TArray<AActor*> TemporaryActors;
	BoxEntrance->GetOverlappingActors(TemporaryActors);
	for(AActor* SingleActor: TemporaryActors)
	{
		if(SingleActor != nullptr)
		{
			EntranceBelt = Cast<ABaseConveyorBelt>(SingleActor);
		}
	}

}

void ABaseMachinery::HandleRawPiecesProduction()
{
	if(RawPieces != 0)
	{
		HandleCorrectOrder();
	}

	if((!EntranceBelt->IsPiecesInConveyor() || RawPieces >= ProductionCapacity || PieceCodeError) && !DoOnce)
	{
		StopConveyorBelt();
		//PieceCodeError = false;
		if(!EntranceBelt->IsPiecesInConveyor())
		{
			ColorCode = FColor::Orange;
		}else if(RawPieces >= ProductionCapacity)
		{
			ColorCode = FColor::Yellow;
		}else if(PieceCodeError)
		{
			ColorCode = FColor::Red;
		}

		DoOnce = true;
	}
	else if((EntranceBelt->IsPiecesInConveyor() && RawPieces < ProductionCapacity && !PieceCodeError && !bInMaintenance) && DoOnce)
	{
		ActivateConveyortBelt();

		if(RawPieces < ProductionCapacity)
		{
			ColorCode = FColor::Green;
		}

		DoOnce = false;
	}

}

void ABaseMachinery::HandleMaintenanceMode()
{
	StopConveyorBelt();
	if(RawPieces == 0)
	{
		bIsPowered = false;
		GetWorldTimerManager().SetTimer(MaintenanceTimer, this, 
			&ABaseMachinery::ExitMaintenanceMode, MaintenanceTimeHold, false);
		DoOnceMantenance = true;
	}

}

void ABaseMachinery::RawPieceEntranceManager()
{	
	GetEntrancePiece();

	if(Piece != nullptr)
	{
		ManageEntrancePiece();
	}

}

void ABaseMachinery::GetEntrancePiece()
{
	BoxEntrance->GetOverlappingActors(ActorsEntrance);
	for(AActor* SinglePiece: ActorsEntrance)
	{
		if(SinglePiece != nullptr)
		{
			Piece = Cast<APiece>(SinglePiece);
		}
	}

}

void ABaseMachinery::ManageEntrancePiece()
{
	if(BoxEntrance->IsOverlappingActor(Piece))
	{
		HoldPieceIndex = Piece->GetPieceCodeIndex();
		ProductionTime = Piece->GetProductionTime();
		PieceSize = Piece->GetSize();

		if(NoOrder == HoldPieceIndex && RawPieces < ProductionCapacity)
		{
			PieceIndex = Piece->GetPieceCodeIndex();
			RawPieces++;
			ProcessCode = Piece->GetPieceProcessCode();

			Piece->DestroyPiece();
			Piece = nullptr;
			PieceCodeError = false;
			bDoOnceStopConveyort = true;
		}else if(NoOrder != HoldPieceIndex && bDoOnceStopConveyort)
		{
			PieceCodeError = true;
			bDoOnceStopConveyort = false;
		}
	}

}

void ABaseMachinery::HandleCorrectOrder()
{	
	IdealPiecesPerMinute = 60.f/ProductionTime;
	if(GetWorldTimerManager().IsTimerActive(MachineTimer) == false && ShouldSpawnProducedPiece())
	{
		GetWorldTimerManager().SetTimer(MachineTimer, this, &ABaseMachinery::ProducedPiecesExitManager, ProductionTime, false);
	}

}

void ABaseMachinery::ActivateConveyortBelt()
{
	if(EntranceBelt != nullptr)
	{
		EntranceBelt->SetConveyorBeltSpeed(50.f);
	}

}

void ABaseMachinery::StopConveyorBelt()
{
	if(EntranceBelt != nullptr)
	{
		EntranceBelt->SetConveyorBeltSpeed(0.f);
	}

}

bool ABaseMachinery::ShouldSpawnProducedPiece()
{
	APiece* OverlapingPiece = nullptr;
	TArray<AActor*> ActorsExit;
	BoxExit->GetOverlappingActors(ActorsExit);
	for(AActor* SinglePiece : ActorsExit)
	{
		if(SinglePiece != nullptr)
		{
			OverlapingPiece = Cast<APiece>(SinglePiece);
		}
	}

	if(BoxExit->IsOverlappingActor(OverlapingPiece))
	{
		return false;
		UE_LOG(LogTemp, Display, TEXT("Cannot spawn more Pieces"));
	}

	return true;
}

void ABaseMachinery::ProducedPiecesExitManager()
{
	UClass* ClassToSpawn = nullptr;
	FRotator ZeroRot = FRotator::ZeroRotator;
	if(ProduceTypePiece != nullptr)
	{
		ClassToSpawn = ProduceTypePiece;
	}

	if(Properties != nullptr)
	{
		Properties->SetPieceProperties(PieceIndex);
		if(ClassToSpawn != nullptr && ProducedPieceMesh != nullptr)
		{
			Product = GetWorld()->SpawnActor<APiece>(ClassToSpawn, SpawnProductLocation, ZeroRot);
			Product->SetPieceBasicProperties(Properties->GetMaterialIndex(), Properties->GetTotalTime());
			Product->SetPieceMeshProperties(ProducedPieceMesh, Properties->GetPieceSize());
			Product->SetPieceProcessCode(ProcessCode);

			GetWorldTimerManager().ClearTimer(MachineTimer);

			RawPieces--;
			ProducedPieces++;
		}
	}
	
}

void ABaseMachinery::ExitMaintenanceMode()
{
	bInMaintenance = false;
	bIsPowered = true;
	DoOnceMantenance = true;
	ActivateConveyortBelt();
}

TSubclassOf<class UUserWidget> ABaseMachinery::GetComputerWidgetClass()
{
    return ComputerClass;

}

void ABaseMachinery::SetbIsPowered(bool bValue)
{
	bIsPowered = bValue;

}

bool ABaseMachinery::IsPowered()
{
	return bIsPowered;

}

int ABaseMachinery::GetProductionCapacity()
{
	return ProductionCapacity;

}

int ABaseMachinery::GetRawPieces()
{
	return RawPieces;

}

int ABaseMachinery::GetProducedPieces()
{
	return ProducedPieces;

}

void ABaseMachinery::SetbInMaintenance(bool bValue)
{
	bInMaintenance = bValue;

}

bool ABaseMachinery::InMaintenance()
{
	return bInMaintenance;

}

void ABaseMachinery::SetProductionOrder(FString Order) //MODIFY TO A NEW FUNTION OR ALERT THE MCHINE COMPUTER WIDGET THAT IT 
{//CANNOT CHANGE THE PRODUCTINORDER IF THE RAWPIECES IS != 0
	if(RawPieces == 0)
	{
		OrderCodes OrderCode = ConverStringToEnum(Order);
		switch (OrderCode)
		{
		case M1_S1:
			NoOrder = 1;
			break;
		case M1_S2:
			NoOrder = 2;
			break;
		case M1_S3:
			NoOrder = 3;
			break;

		case M2_S1:
			NoOrder = 4;
			break;
		case M2_S2:
			NoOrder = 5;
			break;
		case M2_S3:
			NoOrder = 6;
			break;

		case M3_S1:
			NoOrder = 7;
			break;
		case M3_S2:
			NoOrder = 8;
			break;
		case M3_S3:
			NoOrder = 9;
			break;
		
		default:
			NoOrder = 0;
			break;
		}
	}else 
	{
		UE_LOG(LogTemp, Display, TEXT("NOOOUP BABY, not finished!"));
	}

}

FString ABaseMachinery::SetProductionOrderName(int Index)
{
	switch (Index)
	{
	case 1:
		OrderName = "M1S1";
		break;
	case 2:
		OrderName = "M1S2";
		break;
	case 3:
		OrderName = "M1S3";
		break;
	case 4:
		OrderName = "M2S1";
		break;
	case 5:
		OrderName = "M2S2";
		break;
	case 6:
		OrderName = "M2S3";
		break;
	case 7:
		OrderName = "M3S1";
		break;
	case 8:
		OrderName = "M3S2";
		break;
	case 9:
		OrderName = "M3S3";
		break;
	
	default:
		OrderName = "";
		break;
	}

	return OrderName;

}

OrderCodes ABaseMachinery::ConverStringToEnum(FString ToConvert)
{
	std::string Order = std::string(TCHAR_TO_UTF8(*ToConvert));

	static std::map<std::string, OrderCodes> const table = { 
		{"M1S1",OrderCodes::M1_S1}, {"M1S2",OrderCodes::M1_S2},  {"M1S3",OrderCodes::M1_S3}, 
		{"M2S1",OrderCodes::M2_S1}, {"M2S2",OrderCodes::M2_S2},  {"M2S3",OrderCodes::M2_S3},
		{"M3S1",OrderCodes::M3_S1}, {"M3S2",OrderCodes::M3_S2},  {"M3S3",OrderCodes::M3_S3}};
	
	auto iTable = table.find(Order);
	if (iTable != table.end()) 
	{
  		return iTable->second;
	}

	return OrderCodes::NoData_;

}

void ABaseMachinery::NullWidgetTest()
{
	ComputerWidget = nullptr;

}
