// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerCutterWidget.h"
#include "Components/Button.h"

void UComputerCutterWidget::NativeConstruct()
{
    Super::NativeConstruct();



}

///////////////////////////////////// LENGTH PRODUCT BUTTON PROPERTIES ////////////////////////////////
// Section for Length product characteristic buttons.

// Set implementation for Length buttons.
void UComputerCutterWidget::SetLengthsButtonsEvent()
{
    if(L1)
    {
        L1->OnClicked.AddDynamic(this, &UComputerCutterWidget::SetL1ButtonLogic);
    }

    if(L2)
    {
        L2->OnClicked.AddDynamic(this, &UComputerCutterWidget::SetL2ButtonLogic);
    }

    if(L3)
    {
        L3->OnClicked.AddDynamic(this, &UComputerCutterWidget::SetL3ButtonLogic);
    }

}

// Set L1 button logic.
void UComputerCutterWidget::SetL1ButtonLogic()
{
    lengthType = "L1";
    
}

// Set L2 button logic.
void UComputerCutterWidget::SetL2ButtonLogic()
{
    lengthType = "L2";
    
}

// Set L3 button logic.
void UComputerCutterWidget::SetL3ButtonLogic()
{
    lengthType = "L3";
    
}

// Sets implementation for confirmButton.
void UComputerCutterWidget::SetConfirmButton()
{
    if(confirmButton)
    {
        confirmButton->OnClicked.AddDynamic(this, & UComputerCutterWidget::SetConfirmButtonLogic);
    }

}

// Sets confirmButton logic. Triggers an event for machine to recieve production order.
void UComputerCutterWidget::SetConfirmButtonLogic()
{
    confirmProductionCode.ExecuteIfBound(materialType + sizeType + lengthType);

}
