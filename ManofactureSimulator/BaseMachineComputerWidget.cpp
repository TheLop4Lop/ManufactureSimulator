// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMachineComputerWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"

void UBaseMachineComputerWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SetMachineBaseButtons();
    SetConfirmButton();
    SetMachineDoorsButtons();

}

// Sets implementation for machine power and service.
void UBaseMachineComputerWidget::SetMachineBaseButtons()
{
    if(powerButton)
    {
        powerButton->OnClicked.AddDynamic(this, &UBaseMachineComputerWidget::SetPowerButtonLogic);
    }

    if(serviceButton)
    {
        serviceButton->OnClicked.AddDynamic(this, &UBaseMachineComputerWidget::SetServiceButtonLogic);
    }

}

// Implements logic event for Power Button.
void UBaseMachineComputerWidget::SetPowerButtonLogic()
{
    powerAction.ExecuteIfBound();

}

// Implements logic event for Service Button.
void UBaseMachineComputerWidget::SetServiceButtonLogic()
{
    serviceAction.ExecuteIfBound();

}

// Sets implementation for confirmButton.
void UBaseMachineComputerWidget::SetConfirmButton()
{
    if(confirmButton)
    {
        confirmButton->OnClicked.AddDynamic(this, &UBaseMachineComputerWidget::SetConfirmButtonLogic);
    }

}

// Sets confirmButton logic. Triggers an event for machine to recieve production order.
void UBaseMachineComputerWidget::SetConfirmButtonLogic()
{
    ExecuteConfirmButton();

}

void UBaseMachineComputerWidget::ExecuteConfirmButton()
{
    confirmProductionCode.ExecuteIfBound(materialType + sizeType);

}

// Set Machine door buttons.
void UBaseMachineComputerWidget::SetMachineDoorsButtons()
{
    if(productDoorButton)
    {
        productDoorButton->OnClicked.AddDynamic(this, &UBaseMachineComputerWidget::SetProductDoorLogic);
    }

    if(serviceDoorButton)
    {
        serviceDoorButton->OnClicked.AddDynamic(this, &UBaseMachineComputerWidget::SetServiceDoorLogic);
    }

}

// Set ProductDoorButton logic. Triggers an event for machine to open product Door.
void UBaseMachineComputerWidget::SetProductDoorLogic()
{
    productDoorAction.ExecuteIfBound();

}

void UBaseMachineComputerWidget::SetServiceDoorLogic()
{
    serviceDoorAction.ExecuteIfBound();

}

// Set Oil Bar percent level.
void UBaseMachineComputerWidget::SetOilLevel(float oilLevel)
{
    oilLevelBar->SetPercent(oilLevel);

}

// Set Lubricant Bar percent level.
void UBaseMachineComputerWidget::SetLubricantLevel(float lubricantLevel)
{
    lubricantLevelBar->SetPercent(lubricantLevel);

}
