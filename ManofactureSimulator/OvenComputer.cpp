// Fill out your copyright notice in the Description page of Project Settings.


#include "OvenComputer.h"
#include "Kismet/GameplayStatics.h"
#include "ComputerWidgetOven.h"
#include "CharacterController.h"
#include "MachineOven.h"

// Called when the game starts or when spawned
void AOvenComputer::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMachineOven::StaticClass(), actorsInWorld);
	if(actorsInWorld.IsValidIndex(0))
	{
		ovenMachine = Cast<AMachineOven>(actorsInWorld[0]);
		ovenMachine->wrongCodeOnEntrance.BindUObject(this, &AOvenComputer::GetTheWrongCodeOnEntrance);
	}

}

// Called every frame
void AOvenComputer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(ovenMachine && computerWidget)
	{
		computerWidget->SetPowerLight(ovenMachine->GetMachinePower());

		float oilLevel = ((float)ovenMachine->GetOilLevel()/(float)ovenMachine->GetMaxOilLevel());
		computerWidget->SetOilLevel(oilLevel);

		float lubricantLevel = ((float)ovenMachine->GetLubricantLevel()/(float)ovenMachine->GetMaxLubricantLevel());
		computerWidget->SetLubricantLevel(lubricantLevel);

		computerWidget->SetCurrentConfigurationCode(currentProductionCode);
		computerWidget->SetWrongConfigurationCode(productionCodeOnEntrance);
	}

}

// Adds widget and assign the player controller to it.
void AOvenComputer::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	characterController = CharacterController;
	computerWidget = Cast<UComputerWidgetOven>(CreateWidget(characterController, computerClass));

	if(computerWidget)
	{
		computerWidget->AddToViewport();

		computerWidget->confirmProductionCode.BindUObject(this, &AOvenComputer::WidgetBindProductOrder);
		computerWidget->exitButtonEvent.BindUObject(this, &AOvenComputer::PublicWidgetBindResetController);

		computerWidget->powerAction.BindUObject(this, &AOvenComputer::CallPowerAction);
		computerWidget->serviceAction.BindUObject(this, &AOvenComputer::CallServiceAction);

		computerWidget->productDoorAction.BindUObject(this, &AOvenComputer::CallProductDoorAction);
		computerWidget->serviceDoorAction.BindUObject(this, &AOvenComputer::CallsServiceDoorAction);
	}

}

///////////////////////////////////// BASE COMPUTER PROPERTIES ////////////////////////////////
// Sections for the actor properties.

// Resets the character controller to move the character around.
void AOvenComputer::WidgetBindResetController()
{
    characterController->SetMovement(false);
	characterController = nullptr;
    
    computerWidget = nullptr;

}

///////////////////////////////////// MACHINE COMPUTER PROPERTIES ////////////////////////////////
// Sections for the actor properties.

// Calls machine method to change Power Status.
void AOvenComputer::CallPowerAction()
{
	if(ovenMachine)
	{
		ovenMachine->SetMachinePower();
	}

}

// Calls machine method to enter service mode.
void AOvenComputer::CallServiceAction()
{
	if(ovenMachine)
	{
		ovenMachine->StartMachineService();
	}

}

// Gett the product order for pass it on to Storage manager.
void AOvenComputer::WidgetBindProductOrder(FString productCode)
{
	if(ovenMachine)
	{
		ovenMachine->SetProductionMachineOrder(productCode);
		currentProductionCode = productCode;
		productionCodeOnEntrance = "";
	}

}

void AOvenComputer::PublicWidgetBindResetController()
{
    WidgetBindResetController();

}

// Calls machine for product door interaction.
void AOvenComputer::CallProductDoorAction()
{
	if(ovenMachine)
	{
		ovenMachine->SetPositionOfProductDoor();
	}

}

// Calls machine service door for interaction.
void AOvenComputer::CallsServiceDoorAction()
{
	if(ovenMachine)
	{
		ovenMachine->SetPositionOfServiceDoor();
	}

}

// Recieve the wrongCode on entrance by Machine.
void AOvenComputer::GetTheWrongCodeOnEntrance(FString codeOnEntrance)
{
	productionCodeOnEntrance = codeOnEntrance;

}
