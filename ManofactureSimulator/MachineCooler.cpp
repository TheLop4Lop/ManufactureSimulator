// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineCooler.h"
#include "Components/BoxComponent.h"
#include "PaintedProduct.h"

// Sets default values
AMachineCooler::AMachineCooler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	machineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cooler Mesh"));
	RootComponent = machineMesh;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Cooler"));
	boxComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMachineCooler::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMachineCooler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckProductOverlap();

}

void AMachineCooler::CheckProductOverlap()
{
	TArray<AActor*> actorsOnBox;
	boxComponent->GetOverlappingActors(actorsOnBox);

	for(AActor* singleActor : actorsOnBox)
	{
		if(singleActor && singleActor->IsA(APaintedProduct::StaticClass()))
		{
			APaintedProduct* paintedProduct = Cast<APaintedProduct>(singleActor);
			if(paintedProduct)
			{
				paintedProduct->ProductReadyForStorage();
			}
		}
	}

}
