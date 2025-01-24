// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OrderScreen.generated.h"

UCLASS()
class MANOFACTURESIMULATOR_API AOrderScreen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrderScreen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Set the producing order to display.
	void SetProductionOrderOnScreen(FString orderOnProduction);

	// Returns the current producing order to display.
	FString GetProductionOrderOnScreen();

private:
	///////////////////////////////////// ACTOR PROPERTIES ////////////////////////////////
	// Actor properties.

	// Holds reference for Static Mesh
	UPROPERTY(EditAnywhere, Category = "Actor Properties", meta = (AllowPrivateAccess))
	UStaticMeshComponent* screenMesh;

	///////////////////////////////////// PRODUCTION SCREEN PROPERTIES ////////////////////////////////
	// Production Screen actor properties.

	// Holds the Widget class.
	UPROPERTY(EditAnywhere, Category = "Production Screen Properties", meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> screenWidgetClass;

	// Holds reference to WidgetComponent.
	class UWidgetComponent* screenWidgetComponent;

	// Holds reference of the actual Production Screen Widget.
	class UOrderWidget* screenWidget;

	// Holds the production Order.
	FString productionOrder = "";

};
