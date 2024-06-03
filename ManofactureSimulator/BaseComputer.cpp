// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseComputer.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterController.h"
#include "Components/Image.h"
#include "ComputerWidget.h"
#include "BaseStorage.h"
#include "EngineUtils.h"

// Sets default values
ABaseComputer::ABaseComputer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ComputerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Computer Mesh"));
	ComputerMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABaseComputer::BeginPlay()
{
	Super::BeginPlay();
	
	for(ABaseStorage* singleStorage: TActorRange<ABaseStorage>(GetWorld()))
    {
        if(singleStorage != nullptr)
        {
            Storage = singleStorage;
        }
    }
	controlCnt = -1;
	DoOnceCnt = true;
	
}

// Called every frame
void ABaseComputer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(StorageOrdersCommands.Num() > controlCnt + 1 && DoOnceCnt)
	{
		DoOnce = true;
		DoOnceCnt = false;
	}

	if(Storage != nullptr && !Storage->GetbInOrder() && DoOnce)
	{
		DoOnceCnt = true;
		controlCnt++;
		SetOrderToStorage();
		OrderToStorage();

		DoOnce = false;
	}

	if(ComputerWidget != nullptr && Storage != nullptr)
	{
		ComputerWidget->L1Quantity = Storage->GetMinQuantityOrder();
		ComputerWidget->L2Quantity = Storage->GetMiddleQuantityOrder();
		ComputerWidget->L3Quantity = Storage->GetMaxQuantityOrder();
	}

}

void ABaseComputer::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	ComputerWidget = Cast<UComputerWidget>(CreateWidget(CharacterController, ComputerClass));
	ComputerWidget->SetBaseComputer(this);
	ComputerWidget->AddToViewport();

}

void ABaseComputer::SetOrderToStorage()
{
	if(StorageOrdersCommands.Num() != 0)
	{
		FString CurrentPieceCode = StorageOrdersCommands[controlCnt];
		FString stringToInt = "";
		LengthPiece = "";
		for (int index = 0; index < CurrentPieceCode.Len(); )
		{
			while (CurrentPieceCode[index] != 'x')
			{
				stringToInt += CurrentPieceCode[index];
				index++;
			}

			index++;
			while (CurrentPieceCode[index] != '-')
			{
				LengthPiece += CurrentPieceCode[index];
				index++;
			}

			index++;
			PieceCode = CurrentPieceCode.Mid(index);
			break;
		}

		QuantityPieces = FCString::Atoi(*stringToInt);

	}

}

TArray<FString>& ABaseComputer::GetStorageOrderHistorial()
{
	return StorageOrdersCommands;

}

class TSubclassOf<class UUserWidget> ABaseComputer::GetComputerWidgetClass()
{
	return ComputerClass;

}

void ABaseComputer::OrderToStorage()
{
	if(Storage != nullptr)
	{
		if(Storage->CanProduceOrder(QuantityPieces, LengthPiece))
		{
			UE_LOG(LogTemp, Display, TEXT("SI HAAAAAAAAAAAAY CARNAL"));
			Storage->SetOrderQuantityToSpawn(LengthPiece);
			Storage->SetMasterOrder(QuantityPieces, PieceCode);
		}else
		{
			//SOMETHING TO ALERT THAT ORDER IS WRONG
			NoPieceError = true;
			if(ComputerWidget != nullptr)
			{
				ComputerWidget->ErrorLed->SetColorAndOpacity(FColor::Red);
				UE_LOG(LogTemp, Display, TEXT("NNNNNNNNNNNOOOOOOOOOOOOU HAY CARNAL"));
			}	
		}
	}

}

bool ABaseComputer::GetPieceError()
{
	return NoPieceError;

}