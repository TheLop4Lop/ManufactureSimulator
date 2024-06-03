// Fill out your copyright notice in the Description page of Project Settings.


#include "MoldingMachine.h"
#include "Components/SpotLightComponent.h"
#include "ComputerMolderWidget.h"
#include "Components/BoxComponent.h"
#include "PieceSpawnProperties.h"
#include "CharacterController.h"
#include "Piece.h"

void AMoldingMachine::Tick(float DeltaTime)
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

	if(MolderWidget != nullptr)
	{
		MolderWidget->SetWrongOrderName(SetProductionOrderName(PieceIndex));

		if(bInMaintenance)
		{
			MaintenanceHoldSeconds += (GetWorld()->GetDeltaSeconds())/MaintenanceTimeHold;
			MolderWidget->SetMaintenanceBarProgress(MaintenanceHoldSeconds);
		}else/////Problem with the maintenance button, it works when power is off
		{
			MaintenanceHoldSeconds = 0;
			MolderWidget->SetMaintenanceBarProgress(MaintenanceHoldSeconds);
		}
	}

}

void AMoldingMachine::SetMoldingMesh(int Code)
{
    if(MoldingMesh.Num() > 2)
    {
        switch (Code)
        {
        case 0:
            SelectedMesh = MoldingMesh[0];
            TimeMolding = 1.0f;
			CutterCode = "F1";
            break;
        case 1:
            SelectedMesh = MoldingMesh[1];
            TimeMolding = 1.5f;
			CutterCode = "F2";
            break;
        case 2:
            SelectedMesh = MoldingMesh[2];
            TimeMolding = 2.0f;
			CutterCode = "F3";
            break;
        
        default:
            SelectedMesh = MoldingMesh[0];
            TimeMolding = 1.0f;
			CutterCode = "F1";
            break;
        }
    }

}

void AMoldingMachine::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	MolderWidget = Cast<UComputerMolderWidget>(CreateWidget(CharacterController, ComputerClass));
	MolderWidget->SetBaseMachineComputer(this);
	MolderWidget->AddToViewport();

}

void AMoldingMachine::ManageEntrancePiece()
{
   if(BoxEntrance->IsOverlappingActor(Piece))
	{
		HoldPieceIndex = Piece->GetPieceCodeIndex();
		ProductionTime = Piece->GetProductionTime() + TimeMolding;
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

void AMoldingMachine::ProducedPiecesExitManager()
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
		if(ClassToSpawn != nullptr && SelectedMesh != nullptr)
		{
			Product = GetWorld()->SpawnActor<APiece>(ClassToSpawn, SpawnProductLocation, ZeroRot);
			Product->SetPieceBasicProperties(Properties->GetMaterialIndex(), Properties->GetTotalTime());
			Product->SetPieceMeshProperties(SelectedMesh, Properties->GetPieceSize());
			Product->SetPieceProcessCode(ProcessCode + CutterCode);

			GetWorldTimerManager().ClearTimer(MachineTimer);

			RawPieces--;
			ProducedPieces++;
		}
	}

}

void AMoldingMachine::NullWidgetTest()
{
	MolderWidget = nullptr; 

}