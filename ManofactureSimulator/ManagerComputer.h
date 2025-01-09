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
	// Sections for supplier properties. FOR THE MOMENT THIS CLASS ACTS LIKE THE SUPPLIER.

	// Called to ask for raw material. FOR THE MOMENT THIS CLASS ACTS LIKE THE SUPPLIER.
	void ReplenishRawMaterialInStorage(FString rawMaterialCode, int quantity);

	///////////////////////////////////// CUSTOMER PROPERTIES ////////////////////////////////
	// Sections for customer code petitions properties. FOR THE MOMENT THIS CLASS ACTS LIKE THE COSTUMERS.

	// Generates 10 random orders for selection.
	void GenerateOrdersForTheDay();

	// Stores the selected index in computer to hold the ordeds for the day from the Generated Orders.
	void StoreSelectedOrders(TArray<int> selectedOrders);

	// Holds the generated orders for the day to selection.
	TArray<struct FOrderSelection> gneratedOrders;

	// Orders selected on Manager Suppler for orders fo the day.
	TArray<FString> ordersByIndex;

	///////////////////////////////////// GAMEPLAY MONEY LOGIC PROPERTIES ////////////////////////////////
	// For the moment, this class holds the money interaction in game.

	// Holds the value of the current manufactory money.
	float currentMoney = 500.0f;

	// Value needed to buy the selected order.
	float orderCost;

	///////////////////////////////////// ORDER SCREEN PROPERTIES ////////////////////////////////
	// Holds the reference of the orders screen in the world.

	// Holds the tag for upcoming screen.
	UPROPERTY(EditAnywhere, Category = "Order Screens", meta = (AllowPrivateAccess))
	float sellPercent = 0.1f;

	// Holds the tag for upcoming screen.
	UPROPERTY(EditAnywhere, Category = "Order Screens", meta = (AllowPrivateAccess))
	FName upcomingTag;

	// Holds the tag for current screen.
	UPROPERTY(EditAnywhere, Category = "Order Screens", meta = (AllowPrivateAccess))
	FName currentTag;

	// Holds the tag for last screen.
	UPROPERTY(EditAnywhere, Category = "Order Screens", meta = (AllowPrivateAccess))
	FName lastTag;

	// Reference to a order screen in the world, shows NEXT Upcoming Orders of the day.
	class AOrderScreen* upcomingOrderScreen;

	// Reference to a order screen in the world, shows order currently being produced.
	class AOrderScreen* currentOrderScreen;

	// Reference to a order screen in the world, shows tha last order produced.
	class AOrderScreen* lastOrderScreen;

};
