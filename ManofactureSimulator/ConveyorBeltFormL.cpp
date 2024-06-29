// Fill out your copyright notice in the Description page of Project Settings.


#include "ConveyorBeltFormL.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AConveyorBeltFormL::AConveyorBeltFormL()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ConveyorBoxL = CreateDefaultSubobject<UBoxComponent>(TEXT("Machine Exit L"));
	ConveyorBoxL->SetupAttachment(BeltMesh);

	ArrowL = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow L"));
	ArrowL->SetupAttachment(BeltMesh);

}

void AConveyorBeltFormL::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPower && !bInMaintenance)
	{
		ConveyorBox->GetOverlappingActors(Actors);
		ConveyorBoxL->GetOverlappingActors(ActorsL);

		FVector SelfForwardVector = Arrow->GetRelativeRotation().Vector();
		FVector SelfForwardVectorL = ArrowL->GetRelativeRotation().Vector();

		float DeltaSpeed = Speed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

		for (AActor* Actor : Actors)
		{
			if (Actor != nullptr && Actor != this)
			{
				if (ConveyorBox->IsOverlappingActor(Actor))
				{
					Actor->AddActorWorldOffset(SelfForwardVector * DeltaSpeed);
					bPiecesInCoveyor = true;
				}
			}
		}

		for (AActor* Actor : ActorsL)
		{
			if (Actor != nullptr && Actor != this)
			{
				if (ConveyorBoxL->IsOverlappingActor(Actor))
				{
					Actor->AddActorWorldOffset(SelfForwardVectorL * DeltaSpeed);
					bPiecesInCoveyor = true;
				}
			}
		}
	}


	if(bInMaintenance && DoOnce)
	{
		SetConveyorBeltSpeed(0.f);
        GetWorldTimerManager().SetTimer(MaintenanceTimer, this, &AConveyorBeltFormL::HandleMaintenanceMode, MaintenanceTime, false);
		DoOnce = false;
	}

}

void AConveyorBeltFormL::HandleMaintenanceMode()
{
	bPower = true;
	bInMaintenance = false;
	SetConveyorBeltSpeed(50.f);
	DoOnce = true;

}
