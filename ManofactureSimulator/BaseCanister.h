// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "BaseCanister.generated.h"

UCLASS()
class MANOFACTURESIMULATOR_API ABaseCanister : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseCanister();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Method implementation after character interaction, change canister properties for character hold.
	virtual void InteractionFunctionality_Implementation() override;

protected:
	///////////////////////////////////// BASE CANISTER PROPERTIES ////////////////////////////////
	// Section for canister properties.

	// Product Static Mesh
	UPROPERTY(EditAnywhere, Category = "Canister Properties", meta = (AllowPrivateAccess))
	UStaticMeshComponent* canisterMesh;

	///////////////////////////////////// BASE CANISTER INTERACTION ////////////////////////////////
	// Section for canister interaction with character.

	// Restets the behaviour of the mesh to it's original state.
	UFUNCTION()
	void SetCanisterReleaseReset();

	// Holds reference to character for canister event reset.
	class ABaseCharacter* character;

};
