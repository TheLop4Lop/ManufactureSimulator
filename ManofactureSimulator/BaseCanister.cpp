// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCanister.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"

// Sets default values
ABaseCanister::ABaseCanister()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	canisterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Canister Mesh"));
	canisterMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABaseCanister::BeginPlay()
{
	Super::BeginPlay();

	canisterMesh->SetSimulatePhysics(true);
	canisterMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	canisterMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

}

// Called every frame
void ABaseCanister::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

///////////////////////////////////// BASE CANISTER PROPERTIES ////////////////////////////////
// Section for canister properties.

// Returns the the canister liquid MAX capacity.
int ABaseCanister::GetCanisterMaxCapacity()
{
	return maxLiquidCapacity;

}

// Returns the canister liquida level.
int ABaseCanister::GetCanisterCurrentLevel()
{
	return currentLiquid;

}

// Sets new values for the liquid level.
void ABaseCanister::FillCanister()
{
	currentLiquid++;

}

// Removes liquid level from canister.
void ABaseCanister::ReduceCanister()
{
	currentLiquid--;

}

///////////////////////////////////// BASE CANISTER INTERACTION ////////////////////////////////
// Section for canister interaction with character.

// IInteractable interface method for character interaction.
void ABaseCanister::InteractionFunctionality_Implementation()
{
	canisterMesh->SetSimulatePhysics(false);
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if(character)
	{
		character->releaseHold.BindUObject(this, &ABaseCanister::SetCanisterReleaseReset);
		character->releaseComplexHold.BindUObject(this, &ABaseCanister::SetCanisterComplexReleaseReset);
	}

}

void ABaseCanister::SetCanisterReleaseReset()
{
	canisterMesh->SetSimulatePhysics(true);

	character = nullptr;
	
}

// Restets the behaviour of the mesh to it's original state and set location to a specific location.
void ABaseCanister::SetCanisterComplexReleaseReset(UPrimitiveComponent* hitComponent)
{
	if(hitComponent)
	{
		FVector boxLocation = hitComponent->GetComponentLocation();

		AttachToComponent(hitComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SetActorLocation(boxLocation);
		canisterMesh->SetSimulatePhysics(true);

		character = nullptr;
	}

}
