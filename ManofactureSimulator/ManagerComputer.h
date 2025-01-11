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

	///////////////////////////////////// PRODUCTION COST PROPERTIES ////////////////////////////////
	// Section for the piece production cost and product final cost.

	// Section for Material cost (Mx).

	// Holds value of Low Material Cost.
	UPROPERTY(EditAnywhere, Category = "Production Cost - Material", meta = (AllowPrivateAccess))
	float lowQualityCost = 10.0f;

	// Holds value of Low Midd Cost.
	UPROPERTY(EditAnywhere, Category = "Production Cost - Material", meta = (AllowPrivateAccess))
	float middQualityCost = 15.0f;

	// Holds value of Low High Cost.
	UPROPERTY(EditAnywhere, Category = "Production Cost - Material", meta = (AllowPrivateAccess))
	float highQualityCost = 20.0f;

	// Section for Size cost (Sx).

	// Holds value of Small Material Cost.
	UPROPERTY(EditAnywhere, Category = "Production Cost - Size", meta = (AllowPrivateAccess))
	float smallSizeCost = 10.0f;

	// Holds value of Midd Material Cost.
	UPROPERTY(EditAnywhere, Category = "Production Cost - Size", meta = (AllowPrivateAccess))
	float middSizeCost = 15.0f;

	// Holds value of Big Material Cost.
	UPROPERTY(EditAnywhere, Category = "Production Cost - Size", meta = (AllowPrivateAccess))
	float bigSizeCost = 20.0f;

	// Section for Shape cost (Fx).

	// Holds value of Shape 1 Cost.
	UPROPERTY(EditAnywhere, Category = "Production Cost - Shape", meta = (AllowPrivateAccess))
	float f1Cost = 10.5f;

	// Holds value of Shape 2 Cost.
	UPROPERTY(EditAnywhere, Category = "Production Cost - Shape", meta = (AllowPrivateAccess))
	float f2Cost = 11.5f;

	// Holds value of Shape 3 Cost.
	UPROPERTY(EditAnywhere, Category = "Production Cost - Shape", meta = (AllowPrivateAccess))
	float f3Cost = 12.5f;

	// Section for Color cost (Cx).

	// Holds value of Color 1 Cost.
	UPROPERTY(EditAnywhere, Category = "Production Cost - Color", meta = (AllowPrivateAccess))
	float c1Cost = 10.5f;

	// Holds value of Color 1 Cost.
	UPROPERTY(EditAnywhere, Category = "Production Cost - Color", meta = (AllowPrivateAccess))
	float c2Cost = 12.5f;

	// Holds value of Color 1 Cost.
	UPROPERTY(EditAnywhere, Category = "Production Cost - Color", meta = (AllowPrivateAccess))
	float c3Cost = 14.5f;

	// Holds the tag for upcoming screen.
	UPROPERTY(EditAnywhere, Category = "Order Screens", meta = (AllowPrivateAccess))
	float sellPercent = 0.1f;

	// Calculates the value of material by FString.
	float CalculateMaterialProductionCostByString(FString materialCode);

	// Calculates the value of size by FString.
	float CalculateSizeProductionCostByString(FString sizeCode);

	// Calculates the value of shape by FString.
	float CalculateFormProductionCostByString(FString formCode);

	// Calculates the value of color by FString.
	float CalculateColorProductionCostByString(FString colorCode);

	// Updates the current earnings produced to dislay,
	void UpdateCurrentEarnings(FString productCode);
	
	///////////////////////////////////// CUSTOMER PROPERTIES ////////////////////////////////
	// Sections for customer code petitions properties. FOR THE MOMENT THIS CLASS ACTS LIKE THE COSTUMERS.

	// Generates 10 random orders for selection.
	void GenerateOrdersForTheDay();

	// Stores the selected index in computer to hold the ordeds for the day from the Generated Orders.
	void StoreSelectedOrders(TArray<int> selectedOrders, int expected);

	// Holds the generated orders for the day to selection.
	TArray<struct FOrderSelection> gneratedOrders;

	// Orders selected on Manager Suppler for orders fo the day.
	TArray<FString> ordersByIndex;

	// Holds the total amount of exppected earnings as a goal for money production.
	int expectedEarnings;

	// Holds the total amount of current earnings produced.
	int currentEarnings;

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
