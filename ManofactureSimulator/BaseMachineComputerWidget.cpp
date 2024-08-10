// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMachineComputerWidget.h"
#include "Components/Button.h"

void UBaseMachineComputerWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SetConfirmButton();

    SetMachineDoorsButtons();

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
