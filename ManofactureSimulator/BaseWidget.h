// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidget.generated.h"

DECLARE_DELEGATE(FExitEvent);

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	// Delegate for widget exit event.
	FExitEvent exitButtonEvent;

protected:
	///////////////////////////////////// BASE WIDGET PROPERTIES ////////////////////////////////
	// Section for the product share button mechanics for all widgets.

	// Exit button logic.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* exitButton;

	// Set implementation for exitButton.
	void SetExitButtonEvent();

	// Sets the exitButton logic.
	UFUNCTION()
	void ExitButtonPressed();

};
