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

	// Returns the the canister liquid MAX capacity.
	int GetCanisterMaxCapacity();

	// Returns the canister liquida level.
	int GetCanisterCurrentLevel();

	// Sets new values for the liquid level.
	void FillCanister();

	// Removes liquid level from canister.
	void ReduceCanister();

protected:
	///////////////////////////////////// BASE CANISTER PROPERTIES ////////////////////////////////
	// Section for canister properties.

	// Product Static Mesh
	UPROPERTY(EditAnywhere, Category = "Canister Properties", meta = (AllowPrivateAccess))
	UStaticMeshComponent* canisterMesh;

	// Holds the value of the canister MAX capacity.
	UPROPERTY(EditAnywhere, Category = "Canister Properties", meta = (AllowPrivateAccess))
	int maxLiquidCapacity = 50;

	// Holds the value of the actual level of liquid in the canister.
	UPROPERTY(EditAnywhere, Category = "Canister Properties", meta = (AllowPrivateAccess))
	int currentLiquid;

	///////////////////////////////////// BASE CANISTER INTERACTION ////////////////////////////////
	// Section for canister interaction with character.

	// Restets the behaviour of the mesh to it's original state.
	UFUNCTION()
	void SetCanisterReleaseReset();

	// Restets the behaviour of the mesh to it's original state and set location to a specific location.
	UFUNCTION()
	void SetCanisterComplexReleaseReset(UPrimitiveComponent* hitComponent);

	// Holds reference to character for canister event reset.
	class ABaseCharacter* character;

	///////////////////////////////////// BASE CANISTER SOUNDS ////////////////////////////////
	// Section for canister sound properties.

	// Canister grab sound.
	UPROPERTY(EditAnywhere, Category = "Grab Sounds", meta = (AllowPrivateAccess))
	USoundBase* canisterReleasedOnComponentSound;

	// Canister grab sound.
	UPROPERTY(EditAnywhere, Category = "Grab Sounds", meta = (AllowPrivateAccess))
	USoundBase* canisterReleasedFreeSound;

	// Defines the maximum Sound amount.
	UPROPERTY(EditAnywhere, Category = "Grab Sounds", meta = (AllowPrivateAccess))
	float MaxImpulse;

	UFUNCTION()
	void HitSound(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
