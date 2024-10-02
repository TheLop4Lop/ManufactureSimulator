// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerWidgetCutter.h"
#include "Components/Button.h"

void UComputerWidgetCutter::NativeConstruct()
{
    Super::NativeConstruct();

    SetLengthsButtonsEvent();

}

///////////////////////////////////// LENGTH PRODUCT BUTTON PROPERTIES ////////////////////////////////
// Section for Length product characteristic buttons.

// Set implementation for Length buttons.
void UComputerWidgetCutter::SetLengthsButtonsEvent()
{
    if(L1)
    {
        L1->OnClicked.AddDynamic(this, &UComputerWidgetCutter::SetL1ButtonLogic);
    }

    if(L2)
    {
        L2->OnClicked.AddDynamic(this, &UComputerWidgetCutter::SetL2ButtonLogic);
    }

    if(L3)
    {
        L3->OnClicked.AddDynamic(this, &UComputerWidgetCutter::SetL3ButtonLogic);
    }

}

// Set L1 button logic.
void UComputerWidgetCutter::SetL1ButtonLogic()
{
    lengthType = "L1";
    
}

// Set L2 button logic.
void UComputerWidgetCutter::SetL2ButtonLogic()
{
    lengthType = "L2";
    
}

// Set L3 button logic.
void UComputerWidgetCutter::SetL3ButtonLogic()
{
    lengthType = "L3";
    
}

void UComputerWidgetCutter::ExecuteConfirmButton()
{
    confirmProductionCode.ExecuteIfBound(materialType + sizeType + lengthType);

}
