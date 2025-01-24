// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProductWidget.h"
#include "Components/Button.h"

void UBaseProductWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SetMaterialsButtonsEvent();

    SetSizeButtonsEvent();

}

///////////////////////////////////// MATERIAL PRODUCT BUTTON PROPERTIES ////////////////////////////////
// Section for Material product characteristic buttons.

// Set implementation for Material buttons.
void UBaseProductWidget::SetMaterialsButtonsEvent()
{
    if(M1)
    {
        M1->OnClicked.AddDynamic(this, &UBaseProductWidget::SetM1ButtonLogic);
    }

    if(M2)
    {
        M2->OnClicked.AddDynamic(this, &UBaseProductWidget::SetM2ButtonLogic);
    }

    if(M3)
    {
        M3->OnClicked.AddDynamic(this, &UBaseProductWidget::SetM3ButtonLogic);
    }

}

// Set M1 button logic.
void UBaseProductWidget::SetM1ButtonLogic()
{
    materialType = "M1";

}

// Set M2 button logic.
void UBaseProductWidget::SetM2ButtonLogic()
{
    materialType = "M2";

}

// Set M3 button logic.
void UBaseProductWidget::SetM3ButtonLogic()
{
    materialType = "M3";

}

///////////////////////////////////// SIZE PRODUCT BUTTON PROPERTIES ////////////////////////////////
// Section for Size product characteristic buttons.

// Set implementation for Size buttons.
void UBaseProductWidget::SetSizeButtonsEvent()
{
    if(S1)
    {
        S1->OnClicked.AddDynamic(this, &UBaseProductWidget::SetS1ButtonLogic);
    }

    if(S2)
    {
        S2->OnClicked.AddDynamic(this, &UBaseProductWidget::SetS2ButtonLogic);
    }

    if(S3)
    {
        S3->OnClicked.AddDynamic(this, &UBaseProductWidget::SetS3ButtonLogic);
    }

}

// Set S1 button logic.
void UBaseProductWidget::SetS1ButtonLogic()
{
    sizeType = "S1";

}

// Set S2 button logic.
void UBaseProductWidget::SetS2ButtonLogic()
{
    sizeType = "S2";

}

// Set S3 button logic.
void UBaseProductWidget::SetS3ButtonLogic()
{
    sizeType = "S3";

}
