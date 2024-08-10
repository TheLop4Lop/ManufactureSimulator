// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerWidgetPainter.h"
#include "Components/Button.h"

void UComputerWidgetPainter::NativeConstruct()
{
    Super::NativeConstruct();

    SetColorsButtonsEvent();

}

// Set implementation for Form buttons.
void UComputerWidgetPainter::SetColorsButtonsEvent()
{
    if(C1)
    {
        C1->OnClicked.AddDynamic(this, &UComputerWidgetPainter::SetC1ButtonLogic);
    }

    if(C2)
    {
        C2->OnClicked.AddDynamic(this, &UComputerWidgetPainter::SetC2ButtonLogic);
    }

    if(C3)
    {
        C3->OnClicked.AddDynamic(this, &UComputerWidgetPainter::SetC3ButtonLogic);
    }

}

// Set C1 button logic.
void UComputerWidgetPainter::SetC1ButtonLogic()
{
    colorType = "C1";

}

// Set C2 button logic.
void UComputerWidgetPainter::SetC2ButtonLogic()
{
    colorType = "C2";

}

// Set C3 button logic.
void UComputerWidgetPainter::SetC3ButtonLogic()
{
    colorType = "C3";

}

void UComputerWidgetPainter::ExecuteConfirmButton()
{
    confirmProductionCode.ExecuteIfBound(materialType + sizeType + formType + colorType);

}
