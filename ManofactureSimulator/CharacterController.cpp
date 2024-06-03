// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"

void ACharacterController::SetMovement(bool bSet)
{    
    bShowMouseCursor = bSet;
    bEnableClickEvents = bSet;
    bEnableMouseOverEvents = bSet;

}