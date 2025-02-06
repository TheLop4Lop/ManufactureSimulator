// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseComputer.h"
#include "InformationScreen.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API AInformationScreen : public ABaseComputer
{
	GENERATED_BODY()

public:
	// Adds widget and assign the player controller to it.
	virtual void AddWidgetFromComputer(class ACharacterController* CharacterController) override;

protected:

	///////////////////////////////////// MACHINE COMPUTER PROPERTIES ////////////////////////////////
	// Sections for the actor properties.
	
	// Reference to widget Production Widget for manage production machine product.
	class UInformationScreenWidget* screenWidget;
	
};
