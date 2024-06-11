// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"

// Change the controller and interaction on the character, used when widgets are enable or disabled.
void ACharacterController::SetMovement(bool bSet)
{  
    if(bSet)
    {
        DisableInput(this);
        SetInputMode(FInputModeGameAndUI());
    }else
    {
		EnableInput(this);
        SetInputMode(FInputModeGameOnly());
    }

    bShowMouseCursor = bSet;
    bEnableClickEvents = bSet;
    bEnableMouseOverEvents = bSet;

}
