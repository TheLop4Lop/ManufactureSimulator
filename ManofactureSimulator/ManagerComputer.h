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

protected:
	///////////////////////////////////// MANAGER PROPERTIES ////////////////////////////////
	// Sections for Manager Computer properties.

	// Holds reference to Storage Manager in the world.
	class AStorageManager* storageManager;

	// Holds reference to the Production Screen in the wordl.
	class AProductionScreen* productionScreen;

};
