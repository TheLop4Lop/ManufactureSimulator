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
	if(actorsInWorld.IsValidIndex(0)) ovenMachine = Cast<AMachineOven>(actorsInWorld[0]);

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

		computerWidget->productDoorAction.BindUObject(this, &AOvenComputer::CallProductDoorAction);
		computerWidget->serviceDoorAction.BindUObject(this, &AOvenComputer::CallsServiceDoorAction);
	}

}

// Gett the product order for pass it on to Storage manager.
void AOvenComputer::WidgetBindProductOrder(FString productCode)
{
	if(ovenMachine)
	{
		UE_LOG(LogTemp, Display, TEXT("Computer to Machine code: %s"), *productCode);
		ovenMachine->SetProductionMachineOrder(productCode);
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

