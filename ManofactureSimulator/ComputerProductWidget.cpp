// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerProductWidget.h"
#include "Components/Button.h"

void UComputerProductWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SetLengthsButtonsEvent();

    SetOperationButtons();

}

///////////////////////////////////// LENGTH PRODUCT BUTTON PROPERTIES ////////////////////////////////
// Section for Length product characteristic buttons.

// Set implementation for Length buttons.
void UComputerProductWidget::SetLengthsButtonsEvent()
{
    if(L1)
    {
        L1->OnClicked.AddDynamic(this, &UComputerProductWidget::SetL1ButtonLogic);
    }

    if(L2)
    {
        L2->OnClicked.AddDynamic(this, &UComputerProductWidget::SetL2ButtonLogic);
    }

    if(L3)
    {
        L3->OnClicked.AddDynamic(this, &UComputerProductWidget::SetL3ButtonLogic);
    }

}

// Set L1 button logic.
void UComputerProductWidget::SetL1ButtonLogic()
{
    lengthType = "L1";
    
}

// Set L2 button logic.
void UComputerProductWidget::SetL2ButtonLogic()
{
    lengthType = "L2";
    
}

// Set L3 button logic.
void UComputerProductWidget::SetL3ButtonLogic()
{
    lengthType = "L3";
    
}

///////////////////////////////////// COMPUTER BUTTON PROPERTIES ////////////////////////////////
// Section for computer product characteristic orders.

// Set implementation for increment and decrement buttons.
void UComputerProductWidget::SetOperationButtons()
{
    if(increaseButton)
    {
        increaseButton->OnClicked.AddDynamic(this, &UComputerProductWidget::SetIncreaseLogic);
    }

    if(decreaseButton)
    {
        decreaseButton->OnClicked.AddDynamic(this, &UComputerProductWidget::SetDecreaseLogic);
    }

    if(confirmButton)
    {
        confirmButton->OnClicked.AddDynamic(this, &UComputerProductWidget::SetConfirmLogic);
    }

}

// Set increase button logic for number of orders.
void UComputerProductWidget::SetIncreaseLogic()
{
    (productQuantity < 10)? productQuantity++ : productQuantity = 1;

}

// Set decrease button logic for number of orders.
void UComputerProductWidget::SetDecreaseLogic()
{
    (productQuantity > 1)? productQuantity-- : productQuantity = 10;

}

// Set Confirm button logic for orders.
void UComputerProductWidget::SetConfirmLogic()
{
    confirmEvent.ExecuteIfBound(materialType + sizeType + lengthType, productQuantity);

}
