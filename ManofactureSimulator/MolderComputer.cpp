// Fill out your copyright notice in the Description page of Project Settings.


#include "MolderComputer.h"
#include "Kismet/GameplayStatics.h"
#include "ComputerMolderWidget.h"
#include "CharacterController.h"
#include "MachineMolder.h"

// Called when the game starts or when spawned
void AMolderComputer::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMachineMolder::StaticClass(), actorsInWorld);
	if(actorsInWorld.IsValidIndex(0)) cutterMachine = Cast<AMachineMolder>(actorsInWorld[0]);	
	
}

// Adds widget and assign the player controller to it.
void AMolderComputer::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	characterController = CharacterController;
	computerWidget = Cast<UComputerMolderWidget>(CreateWidget(characterController, computerClass));

	if(computerWidget)
	{
		computerWidget->AddToViewport();
		computerWidget->confirmProductionCode.BindUObject(this, &AMolderComputer::WidgetBindProductOrder);
		computerWidget->exitButtonEvent.BindUObject(this, &AMolderComputer::PublicWidgetBindResetController);
	}

}

// Gett the product order for pass it on to Storage manager.
void AMolderComputer::WidgetBindProductOrder(FString productCode)
{
	if(cutterMachine)
	{
		cutterMachine->SetProductionMachineOrder(productCode);
	}

}

void AMolderComputer::PublicWidgetBindResetController()
{
    WidgetBindResetController();

}
