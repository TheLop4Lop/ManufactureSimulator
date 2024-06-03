// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseConveyorBelt.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BaseMachinery.h"

// Sets default values
ABaseConveyorBelt::ABaseConveyorBelt()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BeltMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Belt Mesh"));
	BeltMesh->SetupAttachment(RootComponent);

	ConveyorBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Machine Exit"));
	ConveyorBox->SetupAttachment(BeltMesh);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(BeltMesh);

}

// Called when the game starts or when spawned
void ABaseConveyorBelt::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseConveyorBelt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bPower && !bInMaintenance)
	{
		ConveyorBox->GetOverlappingActors(Actors);

		FVector SelfForwardVector = Arrow->GetRelativeRotation().Vector();
		float DeltaSpeed = Speed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

		for(AActor* Actor: Actors)
		{
			if(Actor != nullptr)
			{
				MachineOwner = Cast<ABaseMachinery>(Actor);
				if(Actor != MachineOwner && Actor != this)
				{
					Actor->AddActorWorldOffset(SelfForwardVector * DeltaSpeed);
					bPiecesInCoveyor = true;
				}else 
				{
					bPiecesInCoveyor = false;
				}
			}
		}
	}

	if(bInMaintenance && DoOnce)
	{
		SetConveyorBeltSpeed(0.f);
		GetWorldTimerManager().SetTimer(MaintenanceTimer, this, &ABaseConveyorBelt::HandleMaintenanceMode, MaintenanceTime, false);
		DoOnce = false;
	}

}

void ABaseConveyorBelt::SetConveyorBeltPower(bool bEnergy)
{
	bPower = bEnergy;

}

void ABaseConveyorBelt::SetConveyorBeltSpeed(float NewFinalSpeed)
{ //Implement increase and decrese
	bShouldConveyorLoop = true;
	if(NewFinalSpeed == 0)
	{
		bVelocityIncrease = false;
		GetWorldTimerManager().SetTimer(ConveyorTimer, this, &ABaseConveyorBelt::ManageConveyorTimer, 0.01f, bShouldConveyorLoop);
	}else if (NewFinalSpeed > Speed)
	{
		bVelocityIncrease = true;
		GetWorldTimerManager().SetTimer(ConveyorTimer, this, &ABaseConveyorBelt::ManageConveyorTimer, 0.05f, bShouldConveyorLoop);
	}

}

void ABaseConveyorBelt::ManageConveyorTimer()
{
	if(bVelocityIncrease)
	{
		if(Speed < 50)
		{
			bPower = true;
			Speed++;
		}
	}	
	else if(Speed > 0)
	{
		Speed--;
		if(Speed == 0)
		{
			//bPower = false;
			bShouldConveyorLoop = false;
		}
	}
}

void ABaseConveyorBelt::HandleMaintenanceMode()
{
	bPower = true;
	bInMaintenance = false;
	SetConveyorBeltSpeed(50.f);
	DoOnce = true;

}

bool ABaseConveyorBelt::IsPiecesInConveyor()
{
	return bPiecesInCoveyor;

}