// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseComputer.h"
#include "CharacterController.h"

// Sets default values
ABaseComputer::ABaseComputer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ComputerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Computer Mesh"));
	ComputerMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABaseComputer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseComputer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Returns the Widget Class, only for pointer reference.
class TSubclassOf<class UUserWidget> ABaseComputer::GetComputerWidgetClass()
{
	return computerClass;

}

// Adds widget and assign the player controller to it.
void ABaseComputer::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	characterController = CharacterController;
	// Implement respective logic for computer widget class.

}

// Resets the character controller to move the character around.
void ABaseComputer::WidgetBindResetController()
{
	characterController->SetMovement(false);
	characterController = nullptr;

}

// Calls to restart controller on player.
void ABaseComputer::PublicWidgetBindResetController()
{
    WidgetBindResetController();

}
