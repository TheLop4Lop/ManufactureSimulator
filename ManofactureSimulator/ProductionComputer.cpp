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
	if(actorsInWorld.IsValidIndex(0))
	{
		storageManager = Cast<AStorageManager>(actorsInWorld[0]);
		storageManager->orderDelivered.BindUObject(this, &AProductionComputer::UpdateDeliverOrders);
	}
	
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

		if(ordersToDeliver.Num() > 0)
		{
			computerWidget->SetOrderBeingDelivered(ordersToDeliver[0]);
		}
	}

}

// Gett the product order for pass it on to Storage manager. INTERPRETARAAAAAAAAAAAAAAAAAAAAAAA
void AProductionComputer::WidgetBindProductOrder(FString productCode, int rawProductQUantity)
{
	if(storageManager)
	{
		FString producedCode;
		if(storageManager->CanProduceProductOrder(productCode, rawProductQUantity) == EStorageProductionStatus::CAN_PRODUCE)
		{
			producedCode = FString::FromInt(rawProductQUantity) + " x " + productCode;

			ordersToDeliver.Add(producedCode);
			computerWidget->SetOrderBeingDelivered(ordersToDeliver[0]);
		}else
		{
			producedCode = "NOT IN STOCK";
			computerWidget->SetOrderBeingDelivered(producedCode);
		}
	}

}

void AProductionComputer::PublicWidgetBindResetController()
{
    WidgetBindResetController();

}

///////////////////////////////////// STORE RAW PRODUCT ORDERS PROPERTIES ////////////////////////////////
// Sections to store the orders by the player to show on widget.

// Called when the StorageManager Delegate fires after deliver a production order.
void AProductionComputer::UpdateDeliverOrders()
{
	if(ordersToDeliver.Num() > 0)
	{
		ordersDelivered.Add(ordersToDeliver[0]);
		ordersToDeliver.RemoveAt(0);

		if(computerWidget) computerWidget->SetOrderBeingDelivered(ordersToDeliver[0]);
	}

}
