// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseComputer.h"
#include "ProductionComputer.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API AProductionComputer : public ABaseComputer
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	// Adds widget and assign the player controller to it.
	virtual void AddWidgetFromComputer(class ACharacterController* CharacterController);

protected:
	///////////////////////////////////// PRODUCTION COMPUTER PROPERTIES ////////////////////////////////
	// Sections for the actor properties.

	// Reference to widget Production Widget for manage Raw Spawn product.
	class UComputerProductWidget* computerWidget;

	// Reference to Storage Manager in the world.
	class AStorageManager* storageManager;

	void PublicWidgetBindResetController();

	// Gett the product order for pass it on to Storage manager.
	void WidgetBindProductOrder(FString productCode, int rawProductQUantity);

	///////////////////////////////////// STORE RAW PRODUCT ORDERS PROPERTIES ////////////////////////////////
	// Sections to store the orders by the player to show on widget.

	// Stores the orders to ask for the Storage Manager.
	TArray<FString> ordersToDeliver;

	// Stores the orders already delivered by the Storage Manager.
	TArray<FString> ordersDelivered;

	// Called when the StorageManager Delegate fires after deliver a production order.
	void UpdateDeliverOrders();
	
};
