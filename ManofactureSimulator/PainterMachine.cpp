// Fill out your copyright notice in the Description page of Project Settings.


#include "PainterMachine.h"
#include "Components/SpotLightComponent.h"
#include "ComputerPainterWidget.h"
#include "Components/BoxComponent.h"
#include "PieceSpawnProperties.h"
#include "CharacterController.h"
#include "Piece.h"

void APainterMachine::Tick(float DeltaTime)
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

	if(PainterWidget != nullptr)
	{
		PainterWidget->SetWrongOrderName(SetProductionOrderName(PieceIndex));

		if(bInMaintenance)
		{
			MaintenanceHoldSeconds += (GetWorld()->GetDeltaSeconds())/MaintenanceTimeHold;
			PainterWidget->SetMaintenanceBarProgress(MaintenanceHoldSeconds);
		}else/////Problem with the maintenance button, it works when power is off
		{
			MaintenanceHoldSeconds = 0;
			PainterWidget->SetMaintenanceBarProgress(MaintenanceHoldSeconds);
		}
	}

}

void APainterMachine::SetPaint(int Code)
{
    if(PaintMaterials.Num() > 2)
    {
        switch (Code)
        {
        case 0:
            SelectedPaint = PaintMaterials[0];
            TimePainting = 1.0f;
			PainterCode = "C1";
            break;
        case 1:
            SelectedPaint = PaintMaterials[1];
            TimePainting = 1.5f;
			PainterCode = "C2";
            break;
        case 2:
            SelectedPaint = PaintMaterials[2];
            TimePainting = 2.0f;
			PainterCode = "C3";
            break;
    
        default:
            SelectedPaint = PaintMaterials[0];
            TimePainting = 1.0f;
			PainterCode = "C1";
            break;
        }
    }

}

void APainterMachine::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	PainterWidget = Cast<UComputerPainterWidget>(CreateWidget(CharacterController, ComputerClass));
	PainterWidget->SetBaseMachineComputer(this);
	PainterWidget->AddToViewport();

}

void APainterMachine::ManageEntrancePiece()
{
    if(BoxEntrance->IsOverlappingActor(Piece))
	{
		HoldPieceIndex = Piece->GetPieceCodeIndex();
		ProductionTime = Piece->GetProductionTime() + TimePainting;
		PieceSize = Piece->GetSize();

		if(NoOrder == HoldPieceIndex && RawPieces < ProductionCapacity)
		{
			PieceIndex = Piece->GetPieceCodeIndex();
			RawPieces++;
            PieceMesh = Piece->GetPieceMesh();
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

void APainterMachine::ProducedPiecesExitManager()
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
		if(ClassToSpawn != nullptr && PieceMesh != nullptr)
		{
			Product = GetWorld()->SpawnActor<APiece>(ClassToSpawn, SpawnProductLocation, ZeroRot);
			Product->SetPieceBasicProperties(Properties->GetMaterialIndex(), Properties->GetTotalTime());
			Product->SetPieceMeshProperties(PieceMesh, Properties->GetPieceSize());
            Product->SetPieceMeshMaterialColor(SelectedPaint);
			Product->SetPieceProcessCode(ProcessCode + PainterCode);

			GetWorldTimerManager().ClearTimer(MachineTimer);

			RawPieces--;
			ProducedPieces++;
		}
	}

}

void APainterMachine::NullWidgetTest()
{
	PainterWidget = nullptr; 

}