// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OrderWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UOrderWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Sets the product code to display on screen.
	void SetProductScreenCode(FString code);

private:
	///////////////////////////////////// ORDERS SCREEN ////////////////////////////////
	// Order screen section to display.

	// Holds reference for Cutter Machine to change color status.
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	FString codeOnScreen;

};
