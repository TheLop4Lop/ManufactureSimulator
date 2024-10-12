// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerQualityWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"

void UComputerQualityWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SetQualityButtons();

}

// Sets implementation of machine buttons.
void UComputerQualityWidget::SetQualityButtons()
{
    if(bPower)
    {
        bPower->OnClicked.AddDynamic(this, &UComputerQualityWidget::SetPowerLogic);
    }

    if(scanButton)
    {
        scanButton->OnClicked.AddDynamic(this, &UComputerQualityWidget::SetScanLogic);
    }

}

// Sets logic for Power button.
void UComputerQualityWidget::SetPowerLogic()
{
    powerAction.ExecuteIfBound();

}

// Sets logic for Scan button.
void UComputerQualityWidget::SetScanLogic()
{
    scanAction.ExecuteIfBound();
    
}

// Sets status for MachinePower.
void UComputerQualityWidget::SetMachinePowerStatus(bool bPowerStatus)
{
    bMachineOn = bPowerStatus;

}

// Sets Product Material.
void UComputerQualityWidget::SetProductMaterial(FString materialCode)
{
    materialQuality = materialCode;

}

// Sets Product Size.
void UComputerQualityWidget::SetProductSize(FString sizeCode)
{
    materialSize = sizeCode;

}

// Sets Product Form.
void UComputerQualityWidget::SetProductForm(FString formCode)
{
    materialForm = formCode;

}

// Sets Product Color.
void UComputerQualityWidget::SetProductColor(FString colorCode)
{
    materialColor = colorCode;

}

// Sets Product Last Proccess.
void UComputerQualityWidget::SetProductLastProccess(FString proccessCode)
{
    materialLastProccess = proccessCode;

}

// Sets ActualQuality progress bar.
void UComputerQualityWidget::SetProductActualQuality(float actualQuality)
{   
    actualQualityBar->SetPercent(actualQuality);
    productActualQuality = actualQuality * 100;

}

// Sets ExpectedQuality progress bar.
void UComputerQualityWidget::SetProducExpectedQuality(float expectedQuality)
{
    expectedQualityBar->SetPercent(expectedQuality);
    productExpectedQuality = expectedQuality * 100;

}
