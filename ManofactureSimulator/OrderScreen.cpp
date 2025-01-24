// Fill out your copyright notice in the Description page of Project Settings.


#include "OrderScreen.h"
#include "Components/WidgetComponent.h"
#include "OrderWidget.h"

// Sets default values
AOrderScreen::AOrderScreen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	screenMesh = CreateDefaultSubobject<UStaticMeshComponent>("Order Screen Mesh");
	RootComponent = screenMesh;

}

// Called when the game starts or when spawned
void AOrderScreen::BeginPlay()
{
	Super::BeginPlay();
	
	screenWidgetComponent = FindComponentByClass<UWidgetComponent>();
	if(screenWidgetComponent && screenWidgetClass)
	{
		screenWidgetComponent->SetWidgetClass(screenWidgetClass);
		screenWidget = Cast<UOrderWidget>(screenWidgetComponent->GetUserWidgetObject());
	}

	if(screenWidget)
	{
		UE_LOG(LogTemp, Display, TEXT("WIDGET ORDER SCREEN FOUND COMPONENT WIDGET"));
	}

}

// Called every frame
void AOrderScreen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Set the producing order to display.
void AOrderScreen::SetProductionOrderOnScreen(FString orderOnProduction)
{
	productionOrder = orderOnProduction;
	if(screenWidget)
	{
		screenWidget->SetProductScreenCode(productionOrder);
	}

}

// Returns the current producing order to display.
FString AOrderScreen::GetProductionOrderOnScreen()
{
	return productionOrder;

}
