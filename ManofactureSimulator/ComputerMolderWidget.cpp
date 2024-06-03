// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerMolderWidget.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "BaseCharacter.h"
#include "MoldingMachine.h"

void UComputerMolderWidget::NativeConstruct()
{
    SetPowerAndMaintenance();

    SetProductionPieceButtons();
    
    SetExitButton();

    SetFigureButtons();

    if(MoldingMachine != nullptr)
    {
        TogglePower = MoldingMachine->IsPowered();

        ChangePowerLedColor();
    }

    FigureConfiguration->SetColorAndOpacity(FColor::Black);

}

void UComputerMolderWidget::SetPowerAndMaintenance()
{
    if(Power)
    {
        Power->OnClicked.AddDynamic(this, &UComputerMolderWidget::PowerButtonClick);
    }

    if(Maintenace)
    {
        Maintenace->OnClicked.AddDynamic(this, &UComputerMolderWidget::MaintenaceButtonClick);
    }

}

void UComputerMolderWidget::PowerButtonClick()
{
    if(MoldingMachine != nullptr)
    {
        TogglePower = !TogglePower;
        MoldingMachine->SetbIsPowered(TogglePower);
        UE_LOG(LogTemp, Display, TEXT("TogglePower: %s"), TogglePower ? TEXT("true") : TEXT("false"));

        ChangePowerLedColor();
    }

}

void UComputerMolderWidget::ChangePowerLedColor()
{
    if(PowerLed)
    {
        (TogglePower) ? LedColor = FColor::Green : LedColor = FColor::Red;
        PowerLed->SetColorAndOpacity(LedColor);
    }

}

void UComputerMolderWidget::MaintenaceButtonClick()
{
    if(MoldingMachine != nullptr)
    {
        bool ButtonMaintenance = MoldingMachine->InMaintenance();
        if(!ButtonMaintenance && MoldingMachine->IsPowered())
        {
            ButtonMaintenance = true;
            MoldingMachine->SetbInMaintenance(ButtonMaintenance);
        }
    }

}

void UComputerMolderWidget::SetMaintenanceBarProgress(float percent)
{
    MaintenanceBar->SetPercent(percent);

}

void UComputerMolderWidget::SetProductionPieceButtons()
{
    if(M1S1)
    {
        M1S1->OnClicked.AddDynamic(this, &UComputerMolderWidget::M1S1ButtonClick);
    }

    if(M1S2)
    {
        M1S2->OnClicked.AddDynamic(this, &UComputerMolderWidget::M1S2ButtonClick);
    }

    if(M1S3)
    {
        M1S3->OnClicked.AddDynamic(this, &UComputerMolderWidget::M1S3ButtonClick);
    }

    if(M2S1)
    {
        M2S1->OnClicked.AddDynamic(this, &UComputerMolderWidget::M2S1ButtonClick);
    }

    if(M2S2)
    {
        M2S2->OnClicked.AddDynamic(this, &UComputerMolderWidget::M2S2ButtonClick);
    }

    if(M2S3)
    {
        M2S3->OnClicked.AddDynamic(this, &UComputerMolderWidget::M2S3ButtonClick);
    }

    if(M3S1)
    {
        M3S1->OnClicked.AddDynamic(this, &UComputerMolderWidget::M3S1ButtonClick);
    }

    if(M3S2)
    {
        M3S2->OnClicked.AddDynamic(this, &UComputerMolderWidget::M3S2ButtonClick);
    }

    if(M3S3)
    {
        M3S3->OnClicked.AddDynamic(this, &UComputerMolderWidget::M3S3ButtonClick);
    }

}

void UComputerMolderWidget::SetBaseMachineComputer(ABaseMachinery* NewComputer)
{
    if(NewComputer != nullptr)
    {
        MoldingMachine = Cast<AMoldingMachine>(NewComputer);
    }

}

void UComputerMolderWidget::M1S1ButtonClick()
{
    StageProduction = "M1S1";

    if(MoldingMachine != nullptr)
    {
        MoldingMachine->SetProductionOrder(StageProduction);
    }

}

void UComputerMolderWidget::M1S2ButtonClick()
{
    StageProduction = "M1S2";

    if(MoldingMachine != nullptr)
    {
        MoldingMachine->SetProductionOrder(StageProduction);
    }

}

void UComputerMolderWidget::M1S3ButtonClick()
{
    StageProduction = "M1S3";

    if(MoldingMachine != nullptr)
    {
        MoldingMachine->SetProductionOrder(StageProduction);
    }

}

void UComputerMolderWidget::M2S1ButtonClick()
{
    StageProduction = "M2S1";

    if(MoldingMachine != nullptr)
    {
        MoldingMachine->SetProductionOrder(StageProduction);
    }
    
}

void UComputerMolderWidget::M2S2ButtonClick()
{
    StageProduction = "M2S2";

    if(MoldingMachine != nullptr)
    {
        MoldingMachine->SetProductionOrder(StageProduction);
    }
    
}

void UComputerMolderWidget::M2S3ButtonClick()
{
    StageProduction = "M2S3";

    if(MoldingMachine != nullptr)
    {
        MoldingMachine->SetProductionOrder(StageProduction);
    }
    
}

void UComputerMolderWidget::M3S1ButtonClick()
{
    StageProduction = "M3S1";

    if(MoldingMachine != nullptr)
    {
        MoldingMachine->SetProductionOrder(StageProduction);
    }
    
}

void UComputerMolderWidget::M3S2ButtonClick()
{
    StageProduction = "M3S2";

    if(MoldingMachine != nullptr)
    {
        MoldingMachine->SetProductionOrder(StageProduction);
    }
    
}

void UComputerMolderWidget::M3S3ButtonClick()
{
    StageProduction = "M3S3";

    if(MoldingMachine != nullptr)
    {
        MoldingMachine->SetProductionOrder(StageProduction);
    }
    
}

void UComputerMolderWidget::SetExitButton()
{
    if(ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UComputerMolderWidget::ExitButtonClick);
    }

}

void UComputerMolderWidget::ExitButtonClick()
{
    Character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if(Character != nullptr)
    {
        Character->ResetMoveInput();
    }

    MoldingMachine->NullWidgetTest();
    MoldingMachine = nullptr;
    RemoveFromParent();

}

void UComputerMolderWidget::SetWrongOrderName(FString Order)
{
    WrongOrderName = Order;

}

///

void UComputerMolderWidget::SetFigureButtons()
{
    if(Figure1)
    {
        Figure1->OnClicked.AddDynamic(this, &UComputerMolderWidget::Figure1ButtonClick);
    }

    if(Figure2)
    {
        Figure2->OnClicked.AddDynamic(this, &UComputerMolderWidget::Figure2ButtonClick);
    }

    if(Figure3)
    {
        Figure3->OnClicked.AddDynamic(this, &UComputerMolderWidget::Figure3ButtonClick);
    }

}

void UComputerMolderWidget::Figure1ButtonClick()
{
    if(MoldingMachine != nullptr)
    {
        MoldingMachine->SetMoldingMesh(0);
        FigureConfiguration->SetColorAndOpacity(FColor::Red);
    }

}

void UComputerMolderWidget::Figure2ButtonClick()
{
    if(MoldingMachine != nullptr)
    {
        MoldingMachine->SetMoldingMesh(1);
        FigureConfiguration->SetColorAndOpacity(FColor::Green);
    }
}

void UComputerMolderWidget::Figure3ButtonClick()
{
    if(MoldingMachine != nullptr)
    {
        MoldingMachine->SetMoldingMesh(2);
        FigureConfiguration->SetColorAndOpacity(FColor::Blue);
    }

}
