// Fill out your copyright notice in the Description page of Project Settings.


#include "PainterComputer.h"
#include "Kismet/GameplayStatics.h"
#include "ComputerPainterWidget.h"
#include "CharacterController.h"
#include "MachinePainter.h"

// Called when the game starts or when spawned
void APainterComputer::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMachinePainter::StaticClass(), actorsInWorld);
	if(actorsInWorld.IsValidIndex(0)) cutterMachine = Cast<AMachinePainter>(actorsInWorld[0]);	
	
}

// Adds widget and assign the player controller to it.
void APainterComputer::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	characterController = CharacterController;
	computerWidget = Cast<UComputerPainterWidget>(CreateWidget(characterController, computerClass));

	if(computerWidget)
	{
		computerWidget->AddToViewport();
		computerWidget->confirmProductionCode.BindUObject(this, &APainterComputer::WidgetBindProductOrder);
		computerWidget->exitButtonEvent.BindUObject(this, &APainterComputer::PublicWidgetBindResetController);
	}

}

// Gett the product order for pass it on to Storage manager.
void APainterComputer::WidgetBindProductOrder(FString productCode)
{
	if(cutterMachine)
	{
		cutterMachine->SetProductionMachineOrder(productCode);
	}

}

void APainterComputer::PublicWidgetBindResetController()
{
    WidgetBindResetController();

}
