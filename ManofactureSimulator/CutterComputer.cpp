// Fill out your copyright notice in the Description page of Project Settings.


#include "CutterComputer.h"
#include "Kismet/GameplayStatics.h"
#include "ComputerCutterWidget.h"
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

// Adds widget and assign the player controller to it.
void ACutterComputer::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	characterController = CharacterController;
	computerWidget = Cast<UComputerCutterWidget>(CreateWidget(characterController, computerClass));

	if(computerWidget)
	{
		computerWidget->AddToViewport();
		computerWidget->confirmProductionCode.BindUObject(this, &ACutterComputer::WidgetBindProductOrder);
		computerWidget->exitButtonEvent.BindUObject(this, &ACutterComputer::PublicWidgetBindResetController);
	}

}

// Gett the product order for pass it on to Storage manager. INTERPRETARAAAAAAAAAAAAAAAAAAAAAAA
void ACutterComputer::WidgetBindProductOrder(FString productCode)
{
	if(cutterMachine)
	{
		cutterMachine->SetProductionMachineOrder(productCode);
	}

}

void ACutterComputer::PublicWidgetBindResetController()
{
    WidgetBindResetController();

}
