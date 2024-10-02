// Fill out your copyright notice in the Description page of Project Settings.


#include "PainterComputer.h"
#include "Kismet/GameplayStatics.h"
#include "ComputerWidgetPainter.h"
#include "CharacterController.h"
#include "MachinePainter.h"

// Called when the game starts or when spawned
void APainterComputer::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMachinePainter::StaticClass(), actorsInWorld);
	if(actorsInWorld.IsValidIndex(0)) painterMachine = Cast<AMachinePainter>(actorsInWorld[0]);	
	
}

// Adds widget and assign the player controller to it.
void APainterComputer::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	characterController = CharacterController;
	computerWidget = Cast<UComputerWidgetPainter>(CreateWidget(characterController, computerClass));

	if(computerWidget)
	{
		computerWidget->AddToViewport();
		computerWidget->confirmProductionCode.BindUObject(this, &APainterComputer::WidgetBindProductOrder);
		computerWidget->exitButtonEvent.BindUObject(this, &APainterComputer::PublicWidgetBindResetController);

		computerWidget->productDoorAction.BindUObject(this, &APainterComputer::CallProductDoorAction);
		computerWidget->serviceDoorAction.BindUObject(this, &APainterComputer::CallsServiceDoorAction);
	}

}

// Gett the product order for pass it on to Storage manager.
void APainterComputer::WidgetBindProductOrder(FString productCode)
{
	if(painterMachine)
	{
		painterMachine->SetProductionMachineOrder(productCode);
	}

}

void APainterComputer::PublicWidgetBindResetController()
{
    WidgetBindResetController();

}

// Calls machine for product door interaction.
void APainterComputer::CallProductDoorAction()
{
	if(painterMachine)
	{
		painterMachine->SetPositionOfProductDoor();
	}

}

// Calls machine service door for interaction.
void APainterComputer::CallsServiceDoorAction()
{
	if(painterMachine)
	{
		painterMachine->SetPositionOfServiceDoor();
	}

}
