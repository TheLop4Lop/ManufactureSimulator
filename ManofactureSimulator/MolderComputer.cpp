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

// Called every frame
void AMolderComputer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(molderMachine && computerWidget)
	{
		computerWidget->SetPowerLight(molderMachine->GetMachinePower());
		
		float oilLevel = ((float)molderMachine->GetOilLevel()/(float)molderMachine->GetMaxOilLevel());
		computerWidget->SetOilLevel(oilLevel);

		float lubricantLevel = ((float)molderMachine->GetLubricantLevel()/(float)molderMachine->GetMaxLubricantLevel());
		computerWidget->SetLubricantLevel(lubricantLevel);
	}

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

		computerWidget->powerAction.BindUObject(this, &AMolderComputer::CallPowerAction);
		computerWidget->serviceAction.BindUObject(this, &AMolderComputer::CallServiceAction);

		computerWidget->productDoorAction.BindUObject(this, &AMolderComputer::CallProductDoorAction);
		computerWidget->serviceDoorAction.BindUObject(this, &AMolderComputer::CallsServiceDoorAction);
	}

}

///////////////////////////////////// BASE COMPUTER PROPERTIES ////////////////////////////////
// Sections for the actor properties.

// Resets the character controller to move the character around.
void AMolderComputer::WidgetBindResetController()
{
    characterController->SetMovement(false);
	characterController = nullptr;
    
    computerWidget = nullptr;

}

///////////////////////////////////// MACHINE COMPUTER PROPERTIES ////////////////////////////////
// Sections for the actor properties.

// Calls machine method to change Power Status.
void AMolderComputer::CallPowerAction()
{
	if(molderMachine)
	{
		molderMachine->SetMachinePower();
	}

}

// Calls machine method to enter service mode.
void AMolderComputer::CallServiceAction()
{
	if(molderMachine)
	{
		molderMachine->StartMachineService();
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
