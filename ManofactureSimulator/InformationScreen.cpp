// Fill out your copyright notice in the Description page of Project Settings.


#include "InformationScreen.h"
#include "InformationScreenWidget.h"

// Adds widget and assign the player controller to it.
void AInformationScreen::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	characterController = CharacterController;
	screenWidget = Cast<UInformationScreenWidget>(CreateWidget(characterController, computerClass));

	if(screenWidget)
	{
		screenWidget->AddToViewport();
		screenWidget->exitButtonEvent.BindUObject(this, &ABaseComputer::PublicWidgetBindResetController);
	}

}
