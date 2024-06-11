// Fill out your copyright notice in the Description page of Project Settings.

#include "ComputerWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"

#define IncrementMax 10
#define DecrementMin 1

void UComputerWidget::NativeConstruct()
{
    InitialPieceQuantity = 1;

    SetQuantityButtons();

    SetLenghtButtons();

    SetMaterialButtons();

    SetSizeButtons();

    SetConfirmExitButtons();

    SetRefreshButtonClick();

}

void UComputerWidget::SetQuantityButtons()
{
    if(IncrementButton)
    {
        IncrementButton->OnClicked.AddDynamic(this, &UComputerWidget::IncrementButtonClick);
    }

    if(DecrementButton)
    {
        DecrementButton->OnClicked.AddDynamic(this, &UComputerWidget::DecrementButtonClick);
    }

}

// Increment or decrement Order quantity
void UComputerWidget::IncrementButtonClick()
{
    InitialPieceQuantity++;

    if(InitialPieceQuantity > IncrementMax)
    {
        InitialPieceQuantity = DecrementMin;
    }

}

void UComputerWidget::DecrementButtonClick()
{
    InitialPieceQuantity--;

    if(InitialPieceQuantity < DecrementMin)
    {
        InitialPieceQuantity = IncrementMax;
    }

}

void UComputerWidget::SetLenghtButtons()
{
    if(L1)
    {
        L1->OnClicked.AddDynamic(this, &UComputerWidget::L1ButtonClick);
    }

    if(L2)
    {
        L2->OnClicked.AddDynamic(this, &UComputerWidget::L2ButtonClick);
    }

    if(L3)
    {
        L3->OnClicked.AddDynamic(this, &UComputerWidget::L3ButtonClick);
    }

}

void UComputerWidget::L1ButtonClick()
{
    LenghtName = "L1";

}

void UComputerWidget::L2ButtonClick()
{
    LenghtName = "L2";

}

void UComputerWidget::L3ButtonClick()
{
    LenghtName = "L3";

}

void UComputerWidget::SetMaterialButtons()
{
    if(M1)
    {
        M1->OnClicked.AddDynamic(this, &UComputerWidget::M1ButtonClick);
    }

    if(M2)
    {
        M2->OnClicked.AddDynamic(this, &UComputerWidget::M2ButtonClick);
    }

    if(M3)
    {
        M3->OnClicked.AddDynamic(this, &UComputerWidget::M3ButtonClick);
    }

}

// Material Type
void UComputerWidget::M1ButtonClick()
{
    MaterialName = "M1";

}

void UComputerWidget::M2ButtonClick()
{
    MaterialName = "M2";

}

void UComputerWidget::M3ButtonClick()
{
    MaterialName = "M3";

}

void UComputerWidget::SetSizeButtons()
{
    if(S1)
    {
        S1->OnClicked.AddDynamic(this, &UComputerWidget::S1ButtonClick);
    }

    if(S2)
    {
        S2->OnClicked.AddDynamic(this, &UComputerWidget::S2ButtonClick);
    }

    if(S3)
    {
        S3->OnClicked.AddDynamic(this, &UComputerWidget::S3ButtonClick);
    }

}

// Material Size
void UComputerWidget::S1ButtonClick()
{
    SizeName = "S1";

}

void UComputerWidget::S2ButtonClick()
{
    SizeName = "S2";

}

void UComputerWidget::S3ButtonClick()
{
    SizeName = "S3";

}

void UComputerWidget::UpdateOrdersTextBlock(const TArray<FString> StringArray)
{
    if (OrdersTextBlock != nullptr)
    {
        FString CombinedText;

        for (const FString Element : StringArray)
        {
            CombinedText += Element + TEXT("\n") + TEXT("\n");
        }

        OrdersTextBlock->SetText(FText::FromString(CombinedText));
    }

}

void UComputerWidget::SetConfirmExitButtons()
{
    if(ConfirmButton)
    {
        ConfirmButton->OnClicked.AddDynamic(this, &UComputerWidget::ConfirmButtonClick);
    }

    if(ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UComputerWidget::ExitButtonClick);
    }

}

void UComputerWidget::ConfirmButtonClick()
{
    orderEvent.ExecuteIfBound(MaterialName + SizeName + LenghtName, InitialPieceQuantity);

}

void UComputerWidget::ExitButtonClick()
{
    exitEvent.ExecuteIfBound();

    RemoveFromParent();

}

void UComputerWidget::SetRefreshButtonClick()
{
    if(RefeshButton)
    {
        RefeshButton->OnClicked.AddDynamic(this, &UComputerWidget::RefreshButtonClick);
    }

}

void UComputerWidget::RefreshButtonClick()
{
    if(OrdersTextBlock != nullptr)
    {
        OrdersTextBlock->SetText(FText::FromString(""));
        TemporaryProducts.Empty();
    }

}
