// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidget.h"
#include "Components/Button.h"

void UBaseWidget::NativeConstruct()
{
    SetExitButtonEvent();

}

// Method for implementing exitButton
void UBaseWidget::SetExitButtonEvent()
{
    if(exitButton)
    {
        exitButton->OnClicked.AddDynamic(this, &UBaseWidget::ExitButtonPressed);
    }

}

// Sets the exitButton logic
void UBaseWidget::ExitButtonPressed()
{
    exitButtonEvent.ExecuteIfBound();
    
    RemoveFromParent();

}
