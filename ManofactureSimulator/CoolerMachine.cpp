// Fill out your copyright notice in the Description page of Project Settings.


#include "CoolerMachine.h"
#include "Components/BoxComponent.h"
#include "PieceSpawnProperties.h"
#include "Piece.h"

void ACoolerMachine::ManageEntrancePiece()
{
    if(BoxEntrance->IsOverlappingActor(Piece))
	{
		HoldPieceIndex = Piece->GetPieceCodeIndex();
		ProductionTime = Piece->GetProductionTime() / Piece->GetProductionTime();
		PieceSize = Piece->GetSize();

		if(NoOrder == HoldPieceIndex && RawPieces < ProductionCapacity)
		{
			PieceIndex = Piece->GetPieceCodeIndex();
			RawPieces++;
            ProductMesh = Piece->GetPieceMesh();
            BakedMaterial = Piece->GetPieceMaterial();
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

void ACoolerMachine::ProducedPiecesExitManager()
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
		if(ClassToSpawn != nullptr && ProductMesh != nullptr)
		{
			Product = GetWorld()->SpawnActor<APiece>(ClassToSpawn, SpawnProductLocation, ZeroRot);
			Product->SetPieceBasicProperties(Properties->GetMaterialIndex(), Properties->GetTotalTime());
			Product->SetPieceMeshProperties(ProductMesh, Properties->GetPieceSize());
            Product->SetPieceMeshMaterialColor(BakedMaterial);
			Product->SetPieceProcessCode(ProcessCode);

			GetWorldTimerManager().ClearTimer(MachineTimer);

			RawPieces--;
			ProducedPieces++;
		}
	}

}
