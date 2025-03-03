// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseComputer.h"
#include "RefuelerComputer.generated.h"

DECLARE_DELEGATE_OneParam(FOilBuy, float)
DECLARE_DELEGATE_OneParam(FLubricantBuy, float)

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API ARefuelerComputer : public ABaseComputer
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Adds widget and assign the player controller to it.
	virtual void AddWidgetFromComputer(class ACharacterController* CharacterController);

	// Delegate to ask money quantity to buy oil.
	FOilBuy oilCostAmount;

	// Delegate to ask money quantity to buy lubricant.
	FLubricantBuy lubricantCostAmount;

	// Sets boolean condition to buy oil.
	void SetOilTransaction(bool oilTransationStatus);

	// Sets boolean condition to buy lubricant.
	void SetLubricantTransaction(bool lubricantTransationStatus);

protected:
	///////////////////////////////////// BASE COMPUTER PROPERTIES ////////////////////////////////
	// Sections for the actor properties.

	// Resets the character controller to move the character around.
	virtual void WidgetBindResetController() override;

	///////////////////////////////////// MACHINE COMPUTER PROPERTIES ////////////////////////////////
	// Sections for the actor properties.
	
	// Reference to widget Production Widget for manage production machine product.
	class UComputerRefuelerWidget* computerWidget;

	// Reference to Refueler machine in the world.
	class ARefueler* refuelerMachine;

	// Changes Machine Power Status.
	void SetPowerStatus();
	
	// Calls machine security door for interaction.
	void CallsSecurityDoorAction();

	// Calls interaction for oil supply
	void CallsOilRefuel();

	// Calls interaction for lubricant supply
	void CallsLubricantRefuel();

	///////////////////////////////////// OIL & LUBRICANT SUPPLY PROPERTIES ////////////////////////////////
	// Section for oil and Lubricant supply.

	// Holds the value of Oil Cost.
	UPROPERTY(EditAnywhere, Category = "Liquids Cost", meta = (AllowPrivateAccess))
	float oilCost = 1.5f;

	// Holds the value of Lubricant Cost.
	UPROPERTY(EditAnywhere, Category = "Liquids Cost", meta = (AllowPrivateAccess))
	float lubricantCost = 0.5f;

	// Holds the calculated oil cost.
	float oilCostToBuy;

	// Holds the calculated lubricant cost.
	float lubricantCostToBuy;

	// Boolean to keep track of oil transaction.
	bool canBuyOil;

	// Boolean to keep track of lubricant transaction.
	bool canBuyLubricant;

	// Calculates the price of oil and buy it from ManagerComputer into Refueler.
	void BuyOilFromSupplier();

	// Calculates the price of lubricant and buy it from ManagerComputer into Refueler.
	void BuyLubricantFromSupplier();
	
};
