// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerWidgetMolder.h"
#include "Components/Button.h"

void UComputerWidgetMolder::NativeConstruct()
{
    Super::NativeConstruct();

    SetFormsButtonsEvent();

}

///////////////////////////////////// FORM PRODUCT BUTTON PROPERTIES ////////////////////////////////
// Section for Form product characteristic buttons.

// Set implementation for Form buttons.
void UComputerWidgetMolder::SetFormsButtonsEvent()
{
    if(F1)
    {
        F1->OnClicked.AddDynamic(this, &UComputerWidgetMolder::SetF1ButtonLogic);
    }

    if(F2)
    {
        F2->OnClicked.AddDynamic(this, &UComputerWidgetMolder::SetF2ButtonLogic);
    }

    if(F3)
    {
        F3->OnClicked.AddDynamic(this, &UComputerWidgetMolder::SetF3ButtonLogic);
    }

}

// Set F1 button logic.
void UComputerWidgetMolder::SetF1ButtonLogic()
{
    formType = "F1";
    
}

// Set F2 button logic.
void UComputerWidgetMolder::SetF2ButtonLogic()
{
    formType = "F2";
    
}

// Set F3 button logic.
void UComputerWidgetMolder::SetF3ButtonLogic()
{
    formType = "F3";
    
}

void UComputerWidgetMolder::ExecuteConfirmButton()
{
    confirmProductionCode.ExecuteIfBound(materialType + sizeType + formType);

}
