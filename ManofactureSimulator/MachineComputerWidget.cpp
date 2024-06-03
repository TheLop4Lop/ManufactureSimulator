// Fill out your copyright notice in the Description page of Project Settings.

#include "MachineComputerWidget.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "BaseCharacter.h"
#include "BaseMachinery.h"

void UMachineComputerWidget::NativeConstruct()
{
    SetPowerAndMaintenance();

    SetProductionPieceButtons();
    
    SetExitButton();

    if(MachineComputer != nullptr)
    {
        TogglePower = MachineComputer->IsPowered();

        ChangePowerLedColor();
    }

}

void UMachineComputerWidget::SetPowerAndMaintenance()
{
    if(Power)
    {
        Power->OnClicked.AddDynamic(this, &UMachineComputerWidget::PowerButtonClick);
    }

    if(Maintenace)
    {
        Maintenace->OnClicked.AddDynamic(this, &UMachineComputerWidget::MaintenaceButtonClick);
    }

}

void UMachineComputerWidget::PowerButtonClick()
{
    if(MachineComputer != nullptr)
    {
        TogglePower = !TogglePower;
        MachineComputer->SetbIsPowered(TogglePower);
        UE_LOG(LogTemp, Display, TEXT("TogglePower: %s"), TogglePower ? TEXT("true") : TEXT("false"));

        ChangePowerLedColor();
    }

}

void UMachineComputerWidget::ChangePowerLedColor()
{
    if(PowerLed)
    {
        (TogglePower) ? LedColor = FColor::Green : LedColor = FColor::Red;          
        PowerLed->SetColorAndOpacity(LedColor);
    }

}

void UMachineComputerWidget::MaintenaceButtonClick()
{
    if(MachineComputer != nullptr)
    {
        bool ButtonMaintenance = MachineComputer->InMaintenance();
        if(!ButtonMaintenance && MachineComputer->IsPowered())
        {
            ButtonMaintenance = true;
            MachineComputer->SetbInMaintenance(ButtonMaintenance);
        }
    }

}

void UMachineComputerWidget::SetMaintenanceBarProgress(float percent)
{
    MaintenanceBar->SetPercent(percent);

}

void UMachineComputerWidget::SetProductionPieceButtons()
{
    if(M1S1)
    {
        M1S1->OnClicked.AddDynamic(this, &UMachineComputerWidget::M1S1ButtonClick);
    }

    if(M1S2)
    {
        M1S2->OnClicked.AddDynamic(this, &UMachineComputerWidget::M1S2ButtonClick);
    }

    if(M1S3)
    {
        M1S3->OnClicked.AddDynamic(this, &UMachineComputerWidget::M1S3ButtonClick);
    }

    if(M2S1)
    {
        M2S1->OnClicked.AddDynamic(this, &UMachineComputerWidget::M2S1ButtonClick);
    }

    if(M2S2)
    {
        M2S2->OnClicked.AddDynamic(this, &UMachineComputerWidget::M2S2ButtonClick);
    }

    if(M2S3)
    {
        M2S3->OnClicked.AddDynamic(this, &UMachineComputerWidget::M2S3ButtonClick);
    }

    if(M3S1)
    {
        M3S1->OnClicked.AddDynamic(this, &UMachineComputerWidget::M3S1ButtonClick);
    }

    if(M3S2)
    {
        M3S2->OnClicked.AddDynamic(this, &UMachineComputerWidget::M3S2ButtonClick);
    }

    if(M3S3)
    {
        M3S3->OnClicked.AddDynamic(this, &UMachineComputerWidget::M3S3ButtonClick);
    }

}

void UMachineComputerWidget::SetBaseMachineComputer(ABaseMachinery* NewComputer)
{
    if(NewComputer != nullptr)
    {
        MachineComputer = NewComputer;
    }

}

void UMachineComputerWidget::M1S1ButtonClick()
{
    StageProduction = "M1S1";

    if(MachineComputer != nullptr)
    {
        MachineComputer->SetProductionOrder(StageProduction);
    }

}

void UMachineComputerWidget::M1S2ButtonClick()
{
    StageProduction = "M1S2";

    if(MachineComputer != nullptr)
    {
        MachineComputer->SetProductionOrder(StageProduction);
    }

}

void UMachineComputerWidget::M1S3ButtonClick()
{
    StageProduction = "M1S3";

    if(MachineComputer != nullptr)
    {
        MachineComputer->SetProductionOrder(StageProduction);
    }

}

void UMachineComputerWidget::M2S1ButtonClick()
{
    StageProduction = "M2S1";

    if(MachineComputer != nullptr)
    {
        MachineComputer->SetProductionOrder(StageProduction);
    }
    
}

void UMachineComputerWidget::M2S2ButtonClick()
{
    StageProduction = "M2S2";

    if(MachineComputer != nullptr)
    {
        MachineComputer->SetProductionOrder(StageProduction);
    }
    
}

void UMachineComputerWidget::M2S3ButtonClick()
{
    StageProduction = "M2S3";

    if(MachineComputer != nullptr)
    {
        MachineComputer->SetProductionOrder(StageProduction);
    }
    
}

void UMachineComputerWidget::M3S1ButtonClick()
{
    StageProduction = "M3S1";

    if(MachineComputer != nullptr)
    {
        MachineComputer->SetProductionOrder(StageProduction);
    }
    
}

void UMachineComputerWidget::M3S2ButtonClick()
{
    StageProduction = "M3S2";

    if(MachineComputer != nullptr)
    {
        MachineComputer->SetProductionOrder(StageProduction);
    }
    
}

void UMachineComputerWidget::M3S3ButtonClick()
{
    StageProduction = "M3S3";

    if(MachineComputer != nullptr)
    {
        MachineComputer->SetProductionOrder(StageProduction);
    }
    
}

void UMachineComputerWidget::SetExitButton()
{
    if(ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UMachineComputerWidget::ExitButtonClick);
    }

}

void UMachineComputerWidget::ExitButtonClick()
{
    Character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if(Character != nullptr)
    {
        Character->ResetMoveInput();
    }

    MachineComputer->NullWidgetTest();
    MachineComputer = nullptr;
    RemoveFromParent();

}

void UMachineComputerWidget::SetWrongOrderName(FString Order)
{
    WrongOrderName = Order;

}
