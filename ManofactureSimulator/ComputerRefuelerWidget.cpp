// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerRefuelerWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UComputerRefuelerWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SetButtonsLogicEvents();
    SetBuyButtonsEvents();

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

///////////////////////////////////// OIL & LUBRICANT SUPPLY PROPERTIES ////////////////////////////////
// Section for oil and Lubricant supply.

// Set buy buttons events.
void UComputerRefuelerWidget::SetBuyButtonsEvents()
{
    if(buyOilButton)
    {
        buyOilButton->OnClicked.AddDynamic(this, &UComputerRefuelerWidget::SetBuyOilButtonLogic);
    }

    if(buyLubricantButton)
    {
        buyLubricantButton->OnClicked.AddDynamic(this, &UComputerRefuelerWidget::SetBuyLubricantButtonLogic);
    }

}

// Set Buy oil Button Logic.
void UComputerRefuelerWidget::SetBuyOilButtonLogic()
{
    buyOil.ExecuteIfBound();

}

// Set Buy lubricant Button Logic.
void UComputerRefuelerWidget::SetBuyLubricantButtonLogic()
{
    buyLubricant.ExecuteIfBound();

}

// Sets the oil cost on Widget.
void UComputerRefuelerWidget::SetOilCost(float oilResetCost)
{
    oilCost->SetText(FText::AsNumber(oilResetCost));

}

// Sets the lubricant cost on Widget.
void UComputerRefuelerWidget::SetLubricantCost(float lubricantResetCost)
{
    lubricantCost->SetText(FText::AsNumber(lubricantResetCost));

}
