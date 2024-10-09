// Fill out your copyright notice in the Description page of Project Settings.


#include "CutterComputer.h"
#include "Kismet/GameplayStatics.h"
#include "ComputerWidgetCutter.h"
#include "CharacterController.h"
#include "MachineCutter.h"

// Called when the game starts or when spawned
void ACutterComputer::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMachineCutter::StaticClass(), actorsInWorld);
	if(actorsInWorld.IsValidIndex(0)) cutterMachine = Cast<AMachineCutter>(actorsInWorld[0]);	
	
}

// Called every frame
void ACutterComputer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(cutterMachine && computerWidget)
	{
		float oilLevel = ((float)cutterMachine->GetOilLevel()/(float)cutterMachine->GetMaxOilLevel());
		computerWidget->SetOilLevel(oilLevel);

		float lubricantLevel = ((float)cutterMachine->GetLubricantLevel()/(float)cutterMachine->GetMaxLubricantLevel());
		computerWidget->SetLubricantLevel(lubricantLevel);
	}

}

// Adds widget and assign the player controller to it.
void ACutterComputer::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	characterController = CharacterController;
	computerWidget = Cast<UComputerWidgetCutter>(CreateWidget(characterController, computerClass));

	if(computerWidget)
	{
		computerWidget->AddToViewport();
		computerWidget->confirmProductionCode.BindUObject(this, &ACutterComputer::WidgetBindProductOrder);
		computerWidget->exitButtonEvent.BindUObject(this, &ABaseComputer::PublicWidgetBindResetController);

		computerWidget->powerAction.BindUObject(this, &ACutterComputer::CallPowerAction);
		computerWidget->serviceAction.BindUObject(this, &ACutterComputer::CallServiceAction);

		computerWidget->productDoorAction.BindUObject(this, &ACutterComputer::CallProductDoorAction);
		computerWidget->serviceDoorAction.BindUObject(this, &ACutterComputer::CallsServiceDoorAction);
	}

}

///////////////////////////////////// BASE COMPUTER PROPERTIES ////////////////////////////////
// Sections for the actor properties.

// Resets the character controller to move the character around.
void ACutterComputer::WidgetBindResetController()
{
    characterController->SetMovement(false);
	characterController = nullptr;
    
    computerWidget = nullptr;

}

///////////////////////////////////// MACHINE COMPUTER PROPERTIES ////////////////////////////////
// Sections for the actor properties.

// Calls machine method to change Power Status.
void ACutterComputer::CallPowerAction()
{
	if(cutterMachine)
	{
		cutterMachine->SetMachinePower();
	}

}

// Calls machine method to enter service mode.
void ACutterComputer::CallServiceAction()
{
	if(cutterMachine)
	{
		cutterMachine->StartMachineService();
	}

}

// Gett the product order for pass it on to Storage manager.
void ACutterComputer::WidgetBindProductOrder(FString productCode)
{
	if(cutterMachine)
	{
		cutterMachine->SetProductionMachineOrder(productCode);
	}

}

// Calls machine for product door interaction.
void ACutterComputer::CallProductDoorAction()
{
	if(cutterMachine)
	{
		cutterMachine->SetPositionOfProductDoor();
	}

}

// Calls machine service door for interaction.
void ACutterComputer::CallsServiceDoorAction()
{
	if(cutterMachine)
	{
		cutterMachine->SetPositionOfServiceDoor();
	}

}
