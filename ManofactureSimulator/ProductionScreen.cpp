// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductionScreen.h"
#include "Components/WidgetComponent.h"
#include "ProductionScreenWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MachineCutter.h"
#include "MachineMolder.h"
#include "MachinePainter.h"
#include "MachineOven.h"
#include "BaseMachine.h"

// Sets default values
AProductionScreen::AProductionScreen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	screenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Production Screen Mesh"));
	RootComponent = screenMesh;

}

// Called when the game starts or when spawned
void AProductionScreen::BeginPlay()
{
	Super::BeginPlay();
	
	screenWidgetComponent = FindComponentByClass<UWidgetComponent>();
	if(screenWidgetComponent && screenWidgetClass)
	{
		screenWidgetComponent->SetWidgetClass(screenWidgetClass);
		screenWidget = Cast<UProductionScreenWidget>(screenWidgetComponent->GetUserWidgetObject());
	}

	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseMachine::StaticClass(), actorsInWorld);
	for(AActor* singleActor : actorsInWorld)
	{
		if(singleActor->IsA(AMachineOven::StaticClass()))
		{
			ovenMachine = Cast<AMachineOven>(singleActor);
		}else if(singleActor->IsA(AMachineCutter::StaticClass()))
		{
			cutterMachine = Cast<AMachineCutter>(singleActor);
		} else if(singleActor->IsA(AMachineMolder::StaticClass()))
		{
			molderMachine = Cast<AMachineMolder>(singleActor);
		}else if(singleActor->IsA(AMachinePainter::StaticClass()))
		{
			painterMachine = Cast<AMachinePainter>(singleActor);
		}
	}

}

// Called every frame
void AProductionScreen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(screenWidget && cutterMachine && molderMachine && painterMachine && ovenMachine)
	{
		screenWidget->SetCutterMachineColorStatus(cutterMachine->GetMachineStatusColor());
		screenWidget->SetMolderMachineColorStatus(molderMachine->GetMachineStatusColor());
		screenWidget->SetPainterMachineColorStatus(painterMachine->GetMachineStatusColor());
		screenWidget->SetOvenMachineColorStatus(ovenMachine->GetMachineStatusColor());

		//screenWidget->SetPiecesProduced(testData);
	}

}
