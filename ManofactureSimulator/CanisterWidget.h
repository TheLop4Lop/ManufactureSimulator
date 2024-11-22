// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CanisterWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UCanisterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Sets the value of liquid level from the canister holded.
	void SetIndicatorCanisterLevel(float currentLevel);

protected:
///////////////////////////////////// COMPUTER REFUELER PROPERTIES ////////////////////////////////
// Section for Computer Refueler buttons.

	// Canister level indicator.
	UPROPERTY(BlueprintReadOnly)
	float indicatorLevel;
	
};
