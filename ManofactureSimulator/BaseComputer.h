// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseComputer.generated.h"

UCLASS()
class MANOFACTURESIMULATOR_API ABaseComputer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseComputer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Returns the Widget Class, only for pointer reference.
	class TSubclassOf<class UUserWidget> GetComputerWidgetClass();

	// Adds widget and assign the player controller to it.
	void AddWidgetFromComputer(class ACharacterController* CharacterController);

private:
	///////////////////////////////////// BASE COMPUTER PROPERTIES ////////////////////////////////
	// Sections for the actor properties.

	// Base Computer actor mesh.
	UPROPERTY(EditAnywhere, Category = "Actor Property", meta = (AllowPrivateAccess))
	UStaticMeshComponent* ComputerMesh;

	// Holds the respective widget class for the computer.
	UPROPERTY(EditAnywhere, Category = "Widgets", meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> computerClass;
	class UComputerWidget* computerWidget;

	// Reference to Storage Manager in the world.
	class AStorageManager* storageManager;

	// Gett the product order for pass it on to Storage manager.
	void WidgetBindProductOrder(FString productCode, int rawProductQUantity);

	// Resets the character controller to move the character around.
	void WidgetBindResetController();

	class ACharacterController* characterController;

};
