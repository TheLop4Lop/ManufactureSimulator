// Fill out your copyright notice in the Description page of Project Settings.


#include "CutterMachine.h"
#include "Components/BoxComponent.h"
#include "InitialPiece.h"

void ACutterMachine::RawPieceEntranceManager()
{
    GetEntrancePiece();

	if(initialPiece != nullptr)
	{
		ManageEntrancePiece();
	}

}

void ACutterMachine::GetEntrancePiece()
{
    BoxEntrance->GetOverlappingActors(ActorsEntrance);
	for(AActor* SinglePiece: ActorsEntrance)
	{
		if(SinglePiece != nullptr)
		{
			initialPiece =  Cast<AInitialPiece>(SinglePiece);
		}
	}

}

void ACutterMachine::ManageEntrancePiece()
{
    if(BoxEntrance->IsOverlappingActor(initialPiece))
	{
		HoldPieceIndex = initialPiece->GetPieceCodeIndex();
		ProductionTime = initialPiece->GetProductionTime();
		PieceSize = initialPiece->GetSize();

		if(NoOrder == HoldPieceIndex && RawPieces < ProductionCapacity)
		{
			PieceIndex = initialPiece->GetPieceCodeIndex();
			ProcessCode = initialPiece->GetPieceProcessCode();
			RawPieces += initialPiece->GetQuantityProduction();

			initialPiece->DestroyPiece();
			initialPiece = nullptr;
			PieceCodeError = false;
			bDoOnceStopConveyort = true;
		}else if(NoOrder != HoldPieceIndex && bDoOnceStopConveyort)
		{
			PieceCodeError = true;
			bDoOnceStopConveyort = false;
		}
	}

}
