// Fill out your copyright notice in the Description page of Project Settings.


#include "RefuelerComputer.h"
#include "Kismet/GameplayStatics.h"
#include "ComputerRefuelerWidget.h"
#include "CharacterController.h"
#include "Refueler.h"

void ARefuelerComputer::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> actorsInWorld;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(),ARefueler::StaticClass(), actorsInWorld);
    if(actorsInWorld.IsValidIndex(0)) refuelerMachine = Cast<ARefueler>(actorsInWorld[0]);

}

// Adds widget and assign the player controller to it.
void ARefuelerComputer::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	characterController = CharacterController;
	computerWidget = Cast<UComputerRefuelerWidget>(CreateWidget(characterController, computerClass));

	if(computerWidget)
	{
		computerWidget->AddToViewport();
		computerWidget->exitButtonEvent.BindUObject(this, &ABaseComputer::PublicWidgetBindResetController);

        computerWidget->doorAction.BindUObject(this, &ARefuelerComputer::CallsSecurityDoorAction);
		computerWidget->oilRefuelAction.BindUObject(this, &ARefuelerComputer::CallsOilRefuel);
		computerWidget->lubricantRefuelAction.BindUObject(this, &ARefuelerComputer::CallsLubricantRefuel);
	}

}

// Calls machine security door for interaction.
void ARefuelerComputer::CallsSecurityDoorAction()
{
    if(refuelerMachine)
    {
        refuelerMachine->SecurityDoorChangePosition();
    }

}

// Calls interaction for oil supply
void ARefuelerComputer::CallsOilRefuel()
{
    if(refuelerMachine)
    {
        refuelerMachine->OilActionButton();
    }

}

// Calls interaction for lubricant supply
void ARefuelerComputer::CallsLubricantRefuel()
{
    if(refuelerMachine)
    {
        refuelerMachine->LubricantActionButton();
    }

}
