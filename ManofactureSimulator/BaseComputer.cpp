// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseComputer.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterController.h"
#include "StorageManager.h"
#include "ComputerWidget.h"

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

	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStorageManager::StaticClass(), actorsInWorld);
	if(actorsInWorld.IsValidIndex(0)) storageManager = Cast<AStorageManager>(actorsInWorld[0]);	
	
}

// Called every frame
void ABaseComputer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Gett the product order for pass it on to Storage manager. INTERPRETARAAAAAAAAAAAAAAAAAAAAAAA
void ABaseComputer::WidgetBindProductOrder(FString productCode, int rawProductQUantity)
{
	if(storageManager)
	{
		storageManager->CanProduceProductOrder(productCode, rawProductQUantity);
	}

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
	computerWidget = Cast<UComputerWidget>(CreateWidget(characterController, computerClass));

	if(computerWidget)
	{
		computerWidget->AddToViewport();
		computerWidget->orderEvent.BindUObject(this, &ABaseComputer::WidgetBindProductOrder);
		computerWidget->exitEvent.BindUObject(this, &ABaseComputer::WidgetBindResetController);
	}

}

// Resets the character controller to move the character around.
void ABaseComputer::WidgetBindResetController()
{
	characterController->SetMovement(false);
	characterController = nullptr;

}
