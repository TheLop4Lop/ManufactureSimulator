// Fill out your copyright notice in the Description page of Project Settings.


#include "Refueler.h"
#include "Components/BoxComponent.h"
#include "LubricantCanister.h"
#include "OilCanister.h"

// Sets default values
ARefueler::ARefueler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	refuelerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Refueler Mesh"));
	RootComponent = refuelerMesh;

	refuelerDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Security Door"));
	refuelerDoor->SetupAttachment(refuelerMesh);

	oilCanisterBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Oil Box"));
	oilCanisterBox->SetupAttachment(refuelerMesh);

	lubricantCanisterBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Lubricant Box"));
	lubricantCanisterBox->SetupAttachment(refuelerMesh);

}

// Called when the game starts or when spawned
void ARefueler::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARefueler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

///////////////////////////////////// REFUELER PROCESS ////////////////////////////////
// Section for Refueler fill canisters process.

// Called from Refueler Computer after widget Security DOOR interaction; Open or Close Security Door.
void ARefueler::SecurityDoorChangePosition()
{
	FRotator doorRotation;
	(!bIsDoorOpen)? doorRotation = FRotator(0.f, 0.f, -100.f) : doorRotation = FRotator(0.f, 0.f,0.f);
	refuelerDoor->SetRelativeRotation(doorRotation);

	bIsDoorOpen = !bIsDoorOpen;

}

// Called from Refueler Computer after widget OIL interaction, if Service door is closed return true, otherwise false.
bool ARefueler::OilActionButton()
{
	if(bIsPowered)
	{
		if(!bIsDoorOpen)
		{
			CheckOilBoxForActorsAction();
			return true;
		}
	}

	return false;
}

// Called from Refueler Computer after widget LUBRICANT interaction, if Service door is closed return true, otherwise false.
bool ARefueler::LubricantActionButton()
{
	if(bIsPowered)
	{
		if(!bIsDoorOpen)
		{
			CheckLubricantBoxForActorsAction();
			return true;
		}
	}

	return false;

}

// Search for actors in lubricantCanisterBox and manages the filling main logic.
void ARefueler::CheckOilBoxForActorsAction()
{
	TArray<AActor*> actorsInOilBox;
	oilCanisterBox->GetOverlappingActors(actorsInOilBox);

	if(actorsInOilBox.Num() == 0 && DoOnceOil)
	{
		UE_LOG(LogTemp, Display, TEXT("CLEAR OIL REFERENCE"));
		GetWorldTimerManager().ClearTimer(oilDepositTimer);
		oilCanister = nullptr;

		DoOnceOil = false;
	}

	if(actorsInOilBox.Num() > 0)
	{
		for(AActor* singleActor : actorsInOilBox)
		{
			if(singleActor->IsA(AOilCanister::StaticClass()) && !GetWorldTimerManager().IsTimerActive(oilDepositTimer))
			{
				UE_LOG(LogTemp, Display, TEXT("PREPARING TO FILL OIL CANISTER"));
				oilCanister = Cast<AOilCanister>(singleActor);
				GetWorldTimerManager().SetTimer(oilDepositTimer, this, &ARefueler::FillUpOilCanister, oilCanisterFillUpTime, true);
				DoOnceOil = true;
			}
		}
	}

}

// Search for actors in lubricantCanisterBox and manages the filling main logic.
void ARefueler::CheckLubricantBoxForActorsAction()
{
	TArray<AActor*> actorsInLubricantBox;
	lubricantCanisterBox->GetOverlappingActors(actorsInLubricantBox);

	if(actorsInLubricantBox.Num() == 0 && DoOnceLubricant)
	{
		UE_LOG(LogTemp, Display, TEXT("CLEAR LUBRICANT REFERENCE"));
		GetWorldTimerManager().ClearTimer(lubricantDepositTimer);
		lubricantCanister = nullptr;

		DoOnceLubricant = false;
	}

	if(actorsInLubricantBox.Num() > 0)
	{
		for(AActor* singleActor : actorsInLubricantBox)
		{
			if(singleActor->IsA(ALubricantCanister::StaticClass()) && !GetWorldTimerManager().IsTimerActive(lubricantDepositTimer))
			{
				UE_LOG(LogTemp, Display, TEXT("PREPARING TO FILL LUBRICANT CANISTER"));
				lubricantCanister = Cast<ALubricantCanister>(singleActor);
				GetWorldTimerManager().SetTimer(lubricantDepositTimer, this, &ARefueler::FillUpLubricantCanister, lubricantCanisterFillUpTime, true);
				DoOnceLubricant = true;
			}
		}
	}

}

void ARefueler::FillUpOilCanister()
{
	if(oilCanister)
	{
		if(oilLevel > 0)
		{
			UE_LOG(LogTemp, Display, TEXT("FILLIN UP OIL CANISTER!"));
			if(oilCanister->GetCanisterCurrentLevel() < oilCanister->GetCanisterMaxCapacity())
			{
				oilCanister->FillCanister();
				oilLevel--;

				UE_LOG(LogTemp, Display, TEXT("OIL LEVEL: %i"), oilLevel);
			}else
			{
				isOilCanisterFull = true;
			}
		}	
	}

}

void ARefueler::FillUpLubricantCanister()
{
	if(lubricantCanister)
	{
		if(lubricantLevel > 0)
		{
			UE_LOG(LogTemp, Display, TEXT("FILLIN UP LUBRICANT CANISTER!"));
			if(lubricantCanister->GetCanisterCurrentLevel() < lubricantCanister->GetCanisterMaxCapacity())
			{
				lubricantCanister->FillCanister();
				lubricantLevel--;

				UE_LOG(LogTemp, Display, TEXT("LUBRICANT LEVEL: %i"), lubricantLevel);
			}else
			{
				isLubricantCanisterFull = true;
			}
		}
	}

}
