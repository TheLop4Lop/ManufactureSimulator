// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerPainterWidget.h"
#include "Components/Button.h"

void UComputerPainterWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SetFormsButtonsEvent();

}

// Set implementation for Form buttons.
void UComputerPainterWidget::SetFormsButtonsEvent()
{
    if(C1)
    {
        C1->OnClicked.AddDynamic(this, &UComputerPainterWidget::SetC1ButtonLogic);
    }

    if(C2)
    {
        C2->OnClicked.AddDynamic(this, &UComputerPainterWidget::SetC2ButtonLogic);
    }

    if(C2)
    {
        C2->OnClicked.AddDynamic(this, &UComputerPainterWidget::SetC2ButtonLogic);
    }

}

// Set C1 button logic.
void UComputerPainterWidget::SetC1ButtonLogic()
{
    colorType = "C1";

}

// Set C2 button logic.
void UComputerPainterWidget::SetC2ButtonLogic()
{
    colorType = "C2";

}

// Set C3 button logic.
void UComputerPainterWidget::SetC3ButtonLogic()
{
    colorType = "C3";

}

// Sets confirmButton logic. Triggers an event for machine to recieve production order.
void UComputerPainterWidget::SetConfirmButtonLogic()
{
    confirmProductionCode.ExecuteIfBound(materialType + sizeType + formType + colorType);

}
