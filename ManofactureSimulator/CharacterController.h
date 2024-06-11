// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API ACharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	// Change the controller and interaction on the character, used when widgets are enable or disabled.
	void SetMovement(bool bSet);
	
};
