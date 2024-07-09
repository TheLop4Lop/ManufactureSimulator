// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerMolderWidget.h"
#include "Components/Button.h"

void UComputerMolderWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SetFormsButtonsEvent();

    SetConfirmButton();

}

///////////////////////////////////// FORM PRODUCT BUTTON PROPERTIES ////////////////////////////////
// Section for Form product characteristic buttons.

// Set implementation for Form buttons.
void UComputerMolderWidget::SetFormsButtonsEvent()
{
    if(F1)
    {
        F1->OnClicked.AddDynamic(this, &UComputerMolderWidget::SetF1ButtonLogic);
    }

    if(F2)
    {
        F2->OnClicked.AddDynamic(this, &UComputerMolderWidget::SetF2ButtonLogic);
    }

    if(F3)
    {
        F3->OnClicked.AddDynamic(this, &UComputerMolderWidget::SetF3ButtonLogic);
    }

}

// Set F1 button logic.
void UComputerMolderWidget::SetF1ButtonLogic()
{
    formType = "F1";
    
}

// Set F2 button logic.
void UComputerMolderWidget::SetF2ButtonLogic()
{
    formType = "F2";
    
}

// Set F3 button logic.
void UComputerMolderWidget::SetF3ButtonLogic()
{
    formType = "F3";
    
}

// Sets implementation for confirmButton.
void UComputerMolderWidget::SetConfirmButton()
{
    if(confirmButton)
    {
        confirmButton->OnClicked.AddDynamic(this, & UComputerMolderWidget::SetConfirmButtonLogic);
    }

}

// Sets confirmButton logic. Triggers an event for machine to recieve production order.
void UComputerMolderWidget::SetConfirmButtonLogic()
{
    confirmProductionCode.ExecuteIfBound(materialType + sizeType + formType);

}
