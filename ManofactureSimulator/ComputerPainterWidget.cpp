// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerPainterWidget.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "BaseCharacter.h"
#include "PainterMachine.h"

void UComputerPainterWidget::NativeConstruct()
{
    SetPowerAndMaintenance();

    SetProductionPieceButtons();
    
    SetExitButton();

    SetFigureButtons();

    if(PainterMachine != nullptr)
    {
        TogglePower = PainterMachine->IsPowered();

        ChangePowerLedColor();
    }

    FigureConfiguration->SetColorAndOpacity(FColor::Black);

}

void UComputerPainterWidget::SetPowerAndMaintenance()
{
    if(Power)
    {
        Power->OnClicked.AddDynamic(this, &UComputerPainterWidget::PowerButtonClick);
    }

    if(Maintenace)
    {
        Maintenace->OnClicked.AddDynamic(this, &UComputerPainterWidget::MaintenaceButtonClick);
    }

}

void UComputerPainterWidget::PowerButtonClick()
{
    if(PainterMachine != nullptr)
    {
        TogglePower = !TogglePower;
        PainterMachine->SetbIsPowered(TogglePower);
        UE_LOG(LogTemp, Display, TEXT("TogglePower: %s"), TogglePower ? TEXT("true") : TEXT("false"));

        ChangePowerLedColor();
    }

}

void UComputerPainterWidget::ChangePowerLedColor()
{
    if(PowerLed)
    {
        (TogglePower) ? LedColor = FColor::Green : LedColor = FColor::Red;          
        PowerLed->SetColorAndOpacity(LedColor);
    }

}

void UComputerPainterWidget::MaintenaceButtonClick()
{
    if(PainterMachine != nullptr)
    {
        bool ButtonMaintenance = PainterMachine->InMaintenance();
        if(!ButtonMaintenance && PainterMachine->IsPowered())
        {
            ButtonMaintenance = true;
            PainterMachine->SetbInMaintenance(ButtonMaintenance);
        }
    }

}

void UComputerPainterWidget::SetMaintenanceBarProgress(float percent)
{
    MaintenanceBar->SetPercent(percent);

}

void UComputerPainterWidget::SetProductionPieceButtons()
{
    if(M1S1)
    {
        M1S1->OnClicked.AddDynamic(this, &UComputerPainterWidget::M1S1ButtonClick);
    }

    if(M1S2)
    {
        M1S2->OnClicked.AddDynamic(this, &UComputerPainterWidget::M1S2ButtonClick);
    }

    if(M1S3)
    {
        M1S3->OnClicked.AddDynamic(this, &UComputerPainterWidget::M1S3ButtonClick);
    }

    if(M2S1)
    {
        M2S1->OnClicked.AddDynamic(this, &UComputerPainterWidget::M2S1ButtonClick);
    }

    if(M2S2)
    {
        M2S2->OnClicked.AddDynamic(this, &UComputerPainterWidget::M2S2ButtonClick);
    }

    if(M2S3)
    {
        M2S3->OnClicked.AddDynamic(this, &UComputerPainterWidget::M2S3ButtonClick);
    }

    if(M3S1)
    {
        M3S1->OnClicked.AddDynamic(this, &UComputerPainterWidget::M3S1ButtonClick);
    }

    if(M3S2)
    {
        M3S2->OnClicked.AddDynamic(this, &UComputerPainterWidget::M3S2ButtonClick);
    }

    if(M3S3)
    {
        M3S3->OnClicked.AddDynamic(this, &UComputerPainterWidget::M3S3ButtonClick);
    }

}

void UComputerPainterWidget::SetBaseMachineComputer(ABaseMachinery* NewComputer)
{
    if(NewComputer != nullptr)
    {
        PainterMachine = Cast<APainterMachine>(NewComputer);
    }

}

void UComputerPainterWidget::M1S1ButtonClick()
{
    StageProduction = "M1S1";

    if(PainterMachine != nullptr)
    {
        PainterMachine->SetProductionOrder(StageProduction);
    }

}

void UComputerPainterWidget::M1S2ButtonClick()
{
    StageProduction = "M1S2";

    if(PainterMachine != nullptr)
    {
        PainterMachine->SetProductionOrder(StageProduction);
    }

}

void UComputerPainterWidget::M1S3ButtonClick()
{
    StageProduction = "M1S3";

    if(PainterMachine != nullptr)
    {
        PainterMachine->SetProductionOrder(StageProduction);
    }

}

void UComputerPainterWidget::M2S1ButtonClick()
{
    StageProduction = "M2S1";

    if(PainterMachine != nullptr)
    {
        PainterMachine->SetProductionOrder(StageProduction);
    }
    
}

void UComputerPainterWidget::M2S2ButtonClick()
{
    StageProduction = "M2S2";

    if(PainterMachine != nullptr)
    {
        PainterMachine->SetProductionOrder(StageProduction);
    }
    
}

void UComputerPainterWidget::M2S3ButtonClick()
{
    StageProduction = "M2S3";

    if(PainterMachine != nullptr)
    {
        PainterMachine->SetProductionOrder(StageProduction);
    }
    
}

void UComputerPainterWidget::M3S1ButtonClick()
{
    StageProduction = "M3S1";

    if(PainterMachine != nullptr)
    {
        PainterMachine->SetProductionOrder(StageProduction);
    }
    
}

void UComputerPainterWidget::M3S2ButtonClick()
{
    StageProduction = "M3S2";

    if(PainterMachine != nullptr)
    {
        PainterMachine->SetProductionOrder(StageProduction);
    }
    
}

void UComputerPainterWidget::M3S3ButtonClick()
{
    StageProduction = "M3S3";

    if(PainterMachine != nullptr)
    {
        PainterMachine->SetProductionOrder(StageProduction);
    }
    
}

void UComputerPainterWidget::SetExitButton()
{
    if(ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UComputerPainterWidget::ExitButtonClick);
    }

}

void UComputerPainterWidget::ExitButtonClick()
{
    Character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if(Character != nullptr)
    {
        Character->ResetMoveInput();
    }

    PainterMachine->NullWidgetTest();
    PainterMachine = nullptr;
    RemoveFromParent();

}

void UComputerPainterWidget::SetWrongOrderName(FString Order)
{
    WrongOrderName = Order;

}

///

void UComputerPainterWidget::SetFigureButtons()
{
    if(Figure1)
    {
        Figure1->OnClicked.AddDynamic(this, &UComputerPainterWidget::Figure1ButtonClick);
    }

    if(Figure2)
    {
        Figure2->OnClicked.AddDynamic(this, &UComputerPainterWidget::Figure2ButtonClick);
    }

    if(Figure3)
    {
        Figure3->OnClicked.AddDynamic(this, &UComputerPainterWidget::Figure3ButtonClick);
    }

}

void UComputerPainterWidget::Figure1ButtonClick()
{
    if(PainterMachine != nullptr)
    {
        PainterMachine->SetPaint(0);
        FigureConfiguration->SetColorAndOpacity(FColor::Red);
    }

}

void UComputerPainterWidget::Figure2ButtonClick()
{
    if(PainterMachine != nullptr)
    {
        PainterMachine->SetPaint(1);
        FigureConfiguration->SetColorAndOpacity(FColor::Green);
    }
}

void UComputerPainterWidget::Figure3ButtonClick()
{
    if(PainterMachine != nullptr)
    {
        PainterMachine->SetPaint(2);
        FigureConfiguration->SetColorAndOpacity(FColor::Blue);
    }

}
