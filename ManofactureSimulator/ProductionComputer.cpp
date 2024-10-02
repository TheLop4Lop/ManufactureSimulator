// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductionComputer.h"
#include "Kismet/GameplayStatics.h"
#include "ComputerProductWidget.h"
#include "CharacterController.h"
#include "StorageManager.h"

// Called when the game starts or when spawned
void AProductionComputer::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStorageManager::StaticClass(), actorsInWorld);
	if(actorsInWorld.IsValidIndex(0)) storageManager = Cast<AStorageManager>(actorsInWorld[0]);	
	
}

// Adds widget and assign the player controller to it.
void AProductionComputer::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	characterController = CharacterController;
	computerWidget = Cast<UComputerProductWidget>(CreateWidget(characterController, computerClass));

	if(computerWidget)
	{
		computerWidget->AddToViewport();
		computerWidget->confirmEvent.BindUObject(this, &AProductionComputer::WidgetBindProductOrder);
		computerWidget->exitButtonEvent.BindUObject(this, &AProductionComputer::PublicWidgetBindResetController);
	}

}

// Gett the product order for pass it on to Storage manager. INTERPRETARAAAAAAAAAAAAAAAAAAAAAAA
void AProductionComputer::WidgetBindProductOrder(FString productCode, int rawProductQUantity)
{
	if(storageManager)
	{
		storageManager->CanProduceProductOrder(productCode, rawProductQUantity);
	}

}

void AProductionComputer::PublicWidgetBindResetController()
{
    WidgetBindResetController();

}
