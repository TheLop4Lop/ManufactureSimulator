// Fill out your copyright notice in the Description page of Project Settings.


#include "MolderComputer.h"
#include "Kismet/GameplayStatics.h"
#include "ComputerWidgetMolder.h"
#include "CharacterController.h"
#include "MachineMolder.h"

// Called when the game starts or when spawned
void AMolderComputer::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMachineMolder::StaticClass(), actorsInWorld);
	if(actorsInWorld.IsValidIndex(0)) molderMachine = Cast<AMachineMolder>(actorsInWorld[0]);	
	
}

// Adds widget and assign the player controller to it.
void AMolderComputer::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	characterController = CharacterController;
	computerWidget = Cast<UComputerWidgetMolder>(CreateWidget(characterController, computerClass));

	if(computerWidget)
	{
		computerWidget->AddToViewport();
		computerWidget->confirmProductionCode.BindUObject(this, &AMolderComputer::WidgetBindProductOrder);
		computerWidget->exitButtonEvent.BindUObject(this, &ABaseComputer::PublicWidgetBindResetController);

		computerWidget->productDoorAction.BindUObject(this, &AMolderComputer::CallProductDoorAction);
		computerWidget->serviceDoorAction.BindUObject(this, &AMolderComputer::CallsServiceDoorAction);
	}

}

// Gett the product order for pass it on to Storage manager.
void AMolderComputer::WidgetBindProductOrder(FString productCode)
{
	if(molderMachine)
	{
		molderMachine->SetProductionMachineOrder(productCode);
	}

}

// Calls machine for product door interaction.
void AMolderComputer::CallProductDoorAction()
{
	if(molderMachine)
	{
		molderMachine->SetPositionOfProductDoor();
	}

}

// Calls machine service door for interaction.
void AMolderComputer::CallsServiceDoorAction()
{
	if(molderMachine)
	{
		molderMachine->SetPositionOfServiceDoor();
	}

}
