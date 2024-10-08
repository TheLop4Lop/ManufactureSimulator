// Fill out your copyright notice in the Description page of Project Settings.


#include "RefuelerComputer.h"
#include "Kismet/GameplayStatics.h"
#include "ComputerRefuelerWidget.h"
#include "CharacterController.h"
#include "Refueler.h"

ARefuelerComputer::ARefuelerComputer()
{
    PrimaryActorTick.bCanEverTick = true;

}

void ARefuelerComputer::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> actorsInWorld;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(),ARefueler::StaticClass(), actorsInWorld);
    if(actorsInWorld.IsValidIndex(0)) refuelerMachine = Cast<ARefueler>(actorsInWorld[0]);

}

// Called every frame
void ARefuelerComputer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(refuelerMachine && computerWidget)
    {
        float oilLevel = ((float)refuelerMachine->GetOilDepositLevel()/(float)refuelerMachine->GetMaxOilDepositLevel());
        computerWidget->SetOilBarLevel(oilLevel);

        float lubricantLevel = ((float)refuelerMachine->GetLubricantDepositLeve()/(float)refuelerMachine->GetMaxLubricantDepositLeve());
        computerWidget->SetLubricantBarLevel(lubricantLevel);
    }

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

///////////////////////////////////// BASE COMPUTER PROPERTIES ////////////////////////////////
// Sections for the actor properties.

// Resets the character controller to move the character around.
void ARefuelerComputer::WidgetBindResetController()
{
    characterController->SetMovement(false);
	characterController = nullptr;
    
    computerWidget = nullptr;

}

///////////////////////////////////// MACHINE COMPUTER PROPERTIES ////////////////////////////////
// Sections for the actor properties.

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
