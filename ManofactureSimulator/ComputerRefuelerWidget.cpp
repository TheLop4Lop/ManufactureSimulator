// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerRefuelerWidget.h"
#include "Components/Button.h"

void UComputerRefuelerWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SetButtonsLogicEvents();

}

void UComputerRefuelerWidget::SetButtonsLogicEvents()
{
    if(bPower)
    {
        bPower->OnClicked.AddDynamic(this, &UComputerRefuelerWidget::SetPowerButtonLogic);
    }

    if(securityDoor)
    {
        securityDoor->OnClicked.AddDynamic(this, &UComputerRefuelerWidget::SetSecurityDoorButtonLogic);
    }

    if(fillOilCanister)
    {
        fillOilCanister->OnClicked.AddDynamic(this, &UComputerRefuelerWidget::SetOilCanisterButtonLogic);
    }

    if(fillLubricantCanister)
    {
        fillLubricantCanister->OnClicked.AddDynamic(this, &UComputerRefuelerWidget::SetlubricantCanisterButtonLogic);
    }

}

// Sets Power button logic implementation.
void UComputerRefuelerWidget::SetPowerButtonLogic()
{
    powerAction.ExecuteIfBound();

}

// Sets SecurityDoor button logic implementation.
void UComputerRefuelerWidget::SetSecurityDoorButtonLogic()
{
    doorAction.ExecuteIfBound();

}

// Sets OilCanister button logic implementation.
void UComputerRefuelerWidget::SetOilCanisterButtonLogic()
{
    oilRefuelAction.ExecuteIfBound();

}

// Sets lubricantCanister button logic implementation.
void UComputerRefuelerWidget::SetlubricantCanisterButtonLogic()
{
    lubricantRefuelAction.ExecuteIfBound();

}
