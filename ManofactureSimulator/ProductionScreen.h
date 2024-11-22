// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProductionScreen.generated.h"

UCLASS()
class MANOFACTURESIMULATOR_API AProductionScreen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProductionScreen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
	class UProductionScreenWidget* screenWidget;

	///////////////////////////////////// PRODUCTION SCREEN MACHINES ////////////////////////////////
	// Production Screen actor properties.

	// Holds reference for CutterMachine.
	class AMachineCutter* cutterMachine;

	// Holds reference for MolderMachine.
	class AMachineMolder* molderMachine;

	// Holds reference for PainterMachine.
	class AMachinePainter* painterMachine;

	// Holds reference for OvenMachine.
	class AMachineOven* ovenMachine;

};
