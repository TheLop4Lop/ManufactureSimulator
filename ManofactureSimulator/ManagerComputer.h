// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseComputer.h"
#include "ManagerComputer.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API AManagerComputer : public ABaseComputer
{
	GENERATED_BODY()
	
public:
	AManagerComputer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Adds widget and assign the player controller to it.
	virtual void AddWidgetFromComputer(class ACharacterController* CharacterController);

protected:
	///////////////////////////////////// MANAGER PROPERTIES ////////////////////////////////
	// Sections for Manager Computer properties.

	// Reference to widget Production Widget for manage production machine product.
	class UManagerSupplierWidget* computerWidget;

	// Holds reference to Storage Manager in the world.
	class AStorageManager* storageManager;

	// Holds reference to the Production Screen in the world.
	class AProductionScreen* productionScreen;

	///////////////////////////////////// SUPPLIER PROPERTIES ////////////////////////////////
	// Sections for supplier properties.

	// Called to ask for raw material. FOR THE MOMENT THIS CLASS ACTS LIKE THE SUPPLIER.
	void ReplenishRawMaterialInStorage(FString rawMaterialCode, int quantity);

	///////////////////////////////////// GAMEPLAY MONEY LOGIC PROPERTIES ////////////////////////////////
	// For the moment, this class holds the money interaction in game.

	// Holds the value of the current manufactory money.
	float currentMoney = 500.0f;

	// Value needed to buy the selected order.
	float orderCost;

};
