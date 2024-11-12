// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerRefuelerWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "Components/Image.h"

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

// Sets value of Oil Bar.
void UComputerRefuelerWidget::SetOilBarLevel(float oilevel)
{
    oilBar->SetPercent(oilevel);

}

// Sets value of Lubricant Bar.
void UComputerRefuelerWidget::SetLubricantBarLevel(float lubricantLevel)
{
    lubricantBar->SetPercent(lubricantLevel);

}

// Sets Power button logic implementation.
void UComputerRefuelerWidget::SetPowerButtonLogic()
{
    powerAction.ExecuteIfBound();

}

// Sets the color of the Power Button Light.
void UComputerRefuelerWidget::SetPowerLight(bool bMachinePower)
{
    if(powerLight)
    {
        FLinearColor powerColor;
        (bMachinePower) ? powerColor = FLinearColor::Green : powerColor = FLinearColor::Red;

        powerLight->SetColorAndOpacity(powerColor);
    }

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
