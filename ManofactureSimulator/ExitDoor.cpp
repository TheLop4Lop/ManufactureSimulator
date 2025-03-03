// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitDoor.h"
#include "Kismet/GameplayStatics.h"
#include "ManagerComputer.h"
#include "ExitDoorWidget.h"

void AExitDoor::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AManagerComputer::StaticClass(), allActors);
	if(allActors.IsValidIndex(0))
	{
		managerComputer = Cast<AManagerComputer>(allActors[0]);
		if(managerComputer)
		{
			GetExitDoorInfo(managerComputer->GetExitDoorInformation());
		}
	}

}

// Adds widget and assign the player controller to it.
void AExitDoor::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	characterController = CharacterController;
	exitDoorWidget = Cast<UExitDoorWidget>(CreateWidget(characterController, computerClass));

	if(exitDoorWidget)
	{
		exitDoorWidget->AddToViewport();
		exitDoorWidget->exitButtonEvent.BindUObject(this, &ABaseComputer::PublicWidgetBindResetController);
	}

}

// Called when the data is obtain for display.
void AExitDoor::GetExitDoorInfo(FExitSimulationInfo exitInfo)
{
	if(managerComputer && exitDoorWidget)
	{
		exitDoorWidget->SetPlayerTimeInProduction(exitInfo.timeSimulated);
		exitDoorWidget->SetTotalProductsProduced(exitInfo.totalProducts);
		exitDoorWidget->SetMostProducedProduct(exitInfo.mostProduced);
		exitDoorWidget->SetTotalEarnings(exitInfo.totalEarnings);
		exitDoorWidget->SetLostMoney(exitInfo.lostMoney);
	}
	
}
