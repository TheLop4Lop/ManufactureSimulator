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

// Called every frame
void ARefuelerComputer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(refuelerMachine && computerWidget)
    {
        computerWidget->SetPowerLight(refuelerMachine->GetMachinePower());
        
        float oilLevel = ((float)refuelerMachine->GetOilDepositLevel()/(float)refuelerMachine->GetMaxOilDepositLevel());
        computerWidget->SetOilBarLevel(oilLevel);

        float lubricantLevel = ((float)refuelerMachine->GetLubricantDepositLeve()/(float)refuelerMachine->GetMaxLubricantDepositLeve());
        computerWidget->SetLubricantBarLevel(lubricantLevel);

        oilCostToBuy = ((float)refuelerMachine->GetMaxOilDepositLevel() - (float)refuelerMachine->GetOilDepositLevel()) * oilCost;
        computerWidget->SetOilCost(oilCostToBuy);

        lubricantCostToBuy = ((float)refuelerMachine->GetMaxLubricantDepositLeve() - (float)refuelerMachine->GetLubricantDepositLeve()) * lubricantCost;
        computerWidget->SetLubricantCost(lubricantCostToBuy);
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

        computerWidget->powerAction.BindUObject(this, &ARefuelerComputer::SetPowerStatus);
        computerWidget->doorAction.BindUObject(this, &ARefuelerComputer::CallsSecurityDoorAction);
		computerWidget->oilRefuelAction.BindUObject(this, &ARefuelerComputer::CallsOilRefuel);
		computerWidget->lubricantRefuelAction.BindUObject(this, &ARefuelerComputer::CallsLubricantRefuel);

        computerWidget->buyOil.BindUObject(this, &ARefuelerComputer::BuyOilFromSupplier);
        computerWidget->buyLubricant.BindUObject(this, &ARefuelerComputer::BuyLubricantFromSupplier);
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

// Changes Machine Power Status.
void ARefuelerComputer::SetPowerStatus()
{
    if(refuelerMachine)
    {
        refuelerMachine->SetMachinePower();
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

///////////////////////////////////// OIL & LUBRICANT SUPPLY PROPERTIES ////////////////////////////////
// Section for oil and Lubricant supply.

// Calculates the price of oil and buy it from ManagerComputer into Refueler.
void ARefuelerComputer::BuyOilFromSupplier()
{
    if(refuelerMachine)
    {
        oilCostAmount.ExecuteIfBound(oilCostToBuy);
        if(canBuyOil)
        {
            refuelerMachine->ResetUpTheOilDeposit();
        }
    }
    canBuyOil = false; // Reset value.

}

// Calculates the price of lubricant and buy it from ManagerComputer into Refueler.
void ARefuelerComputer::BuyLubricantFromSupplier()
{
    if(refuelerMachine)
    {
        lubricantCostAmount.ExecuteIfBound(lubricantCostToBuy);
        if(canBuyLubricant)
        {
            refuelerMachine->ResetUpTheLubricantDeposit();
        }
    }
    canBuyLubricant = false; // Reset value.

}

// Sets boolean condition to buy oil.
void ARefuelerComputer::SetOilTransaction(bool oilTransationStatus)
{
    canBuyOil = oilTransationStatus;

}

// Sets boolean condition to buy lubricant.
void ARefuelerComputer::SetLubricantTransaction(bool lubricantTransationStatus)
{
    canBuyLubricant = lubricantTransationStatus;

}
