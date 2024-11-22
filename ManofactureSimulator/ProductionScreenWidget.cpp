// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductionScreenWidget.h"
#include "Components/Image.h"

// Sets Cutter Machine color Status.
void UProductionScreenWidget::SetCutterMachineColorStatus(FColor machineStatus)
{
    FLinearColor machineColor = FLinearColor(machineStatus);
    cutterImage->SetColorAndOpacity(machineColor);

}

// Sets Molder Machine color Status.
void UProductionScreenWidget::SetMolderMachineColorStatus(FColor machineStatus)
{
    FLinearColor machineColor = FLinearColor(machineStatus);
    molderImage->SetColorAndOpacity(machineColor);

}

// Sets Painter Machine color Status.
void UProductionScreenWidget::SetPainterMachineColorStatus(FColor machineStatus)
{
    FLinearColor machineColor = FLinearColor(machineStatus);
    painterImage->SetColorAndOpacity(machineColor);

}

// Sets Oven Machine color Status.
void UProductionScreenWidget::SetOvenMachineColorStatus(FColor machineStatus)
{
    FLinearColor machineColor = FLinearColor(machineStatus);
    ovenImage->SetColorAndOpacity(machineColor);

}

void UProductionScreenWidget::SetPiecesProduced(int data)
{
    producedPieces = data;

}
