// Fill out your copyright notice in the Description page of Project Settings.


#include "OvenMachine.h"
#include "Components/BoxComponent.h"
#include "PieceSpawnProperties.h"
#include "Piece.h"

void AOvenMachine::SetBakedColor(UMaterial* Color)
{
    if(Color != nullptr)
    {
        if(FreshMaterial.Num() > 2)
        {
            if(Color->GetMaterial()->GetName() == FreshMaterial[0]->GetMaterial()->GetName())
            {
                BakedColor = BakedMaterial[0];
                BakeTime = 2.0f;
            }else if(Color->GetMaterial()->GetName() == FreshMaterial[1]->GetMaterial()->GetName())
            {
                BakedColor = BakedMaterial[1];
                BakeTime = 2.2f;
            }else if(Color->GetMaterial()->GetName() == FreshMaterial[2]->GetMaterial()->GetName())
            {
                BakedColor = BakedMaterial[2];
                BakeTime = 2.5f;
            }
        }
    }

}

void AOvenMachine::ManageEntrancePiece()
{
    if(BoxEntrance->IsOverlappingActor(Piece))
	{
		HoldPieceIndex = Piece->GetPieceCodeIndex();
		ProductionTime = Piece->GetProductionTime() + BakeTime;
		PieceSize = Piece->GetSize();

		if(NoOrder == HoldPieceIndex && RawPieces < ProductionCapacity)
		{
			PieceIndex = Piece->GetPieceCodeIndex();
			RawPieces++;
            ProductMesh = Piece->GetPieceMesh();
            SetBakedColor(Piece->GetPieceMaterial());
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

void AOvenMachine::ProducedPiecesExitManager()
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
            Product->SetPieceMeshMaterialColor(BakedColor);
			Product->SetPieceProcessCode(ProcessCode);

			GetWorldTimerManager().ClearTimer(MachineTimer);

			RawPieces--;
			ProducedPieces++;
		}
	}

}
