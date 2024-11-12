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

	refuelerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Refueler Root"));
	RootComponent = refuelerRoot;

	refuelerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Refueler Mesh"));
	refuelerMesh->SetupAttachment(refuelerRoot);

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

// Called frm Refueler Computer after widget Power interactio; change status between ON and OFF.
void ARefueler::SetMachinePower()
{
	bIsPowered = !bIsPowered;

}

// Gets power status for widget interaction.
bool ARefueler::GetMachinePower()
{
	return bIsPowered;

}

// Called from Refueler Computer after widget Security DOOR interaction; Open or Close Security Door.
void ARefueler::SecurityDoorChangePosition()
{
	FRotator doorRotation;
	(!bIsDoorOpen)? doorRotation = FRotator(0.f, 100.f, 0.f) : doorRotation = FRotator(0.f, 0.f,0.f);
	refuelerDoor->SetRelativeRotation(doorRotation);

	bIsDoorOpen = !bIsDoorOpen;
	if(GetWorldTimerManager().IsTimerActive(oilDepositTimer)) GetWorldTimerManager().ClearTimer(oilDepositTimer);
	if(GetWorldTimerManager().IsTimerActive(lubricantDepositTimer)) GetWorldTimerManager().ClearTimer(oilDepositTimer);

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
			UE_LOG(LogTemp, Display, TEXT("CALLING TO FILL CANISTER"));
			CheckLubricantBoxForActorsAction();
			return true;
		}
	}

	return false;

}

// Called from Manager Computer to fill Oil Deposit.
void ARefueler::FillOilDepositAction()
{
	if(bIsPowered) SetMachinePower();
	GetWorldTimerManager().ClearTimer(oilDepositTimer);
	GetWorldTimerManager().SetTimer(oilDepositTimer, this, &ARefueler::FillUpOilDeposit, oilDepositFillUpTime, (oilLevel < maxOilCapacity));

}

// Called from Manager Computer to fill Lubricant Deposit.
void ARefueler::FillLubricantDepositAction()
{
	if(bIsPowered) SetMachinePower();
	GetWorldTimerManager().ClearTimer(lubricantDepositTimer);
	GetWorldTimerManager().SetTimer(lubricantDepositTimer, this, &ARefueler::FillUpLubricantDeposit, lubricantDepositFillUpTime, (oilLevel < maxOilCapacity));

}

// Search for actors in lubricantCanisterBox and manages the filling main logic.
void ARefueler::CheckOilBoxForActorsAction()
{
	TArray<AActor*> actorsInOilBox;
	oilCanisterBox->GetOverlappingActors(actorsInOilBox);

	if(actorsInOilBox.Num() == 0)
	{
		GetWorldTimerManager().ClearTimer(oilDepositTimer);
		isOilCanisterFull = false;
		oilCanister = nullptr;
	}

	if(actorsInOilBox.Num() > 0)
	{
		for(AActor* singleActor : actorsInOilBox)
		{
			if(singleActor->IsA(AOilCanister::StaticClass()) && !GetWorldTimerManager().IsTimerActive(oilDepositTimer))
			{
				oilCanister = Cast<AOilCanister>(singleActor);
				GetWorldTimerManager().SetTimer(oilDepositTimer, this, &ARefueler::FillUpOilCanister, oilCanisterFillUpTime, true);
			}
		}
	}

}

// Search for actors in lubricantCanisterBox and manages the filling main logic.
void ARefueler::CheckLubricantBoxForActorsAction()
{
	TArray<AActor*> actorsInLubricantBox;
	lubricantCanisterBox->GetOverlappingActors(actorsInLubricantBox);

	if(actorsInLubricantBox.Num() == 0)
	{
		GetWorldTimerManager().ClearTimer(lubricantDepositTimer);
		isLubricantCanisterFull = false;
		lubricantCanister = nullptr;
	}

	if(actorsInLubricantBox.Num() > 0)
	{
		for(AActor* singleActor : actorsInLubricantBox)
		{
			if(singleActor->IsA(ALubricantCanister::StaticClass()) && !GetWorldTimerManager().IsTimerActive(lubricantDepositTimer))
			{
				lubricantCanister = Cast<ALubricantCanister>(singleActor);
				GetWorldTimerManager().SetTimer(lubricantDepositTimer, this, &ARefueler::FillUpLubricantCanister, lubricantCanisterFillUpTime, true);
			}
		}
	}

}

void ARefueler::FillUpOilCanister()
{
	if(oilCanister && !isOilCanisterFull)
	{
		if(oilLevel > 0)
		{
			if(oilCanister->GetCanisterCurrentLevel() < oilCanister->GetCanisterMaxCapacity())
			{
				oilCanister->FillCanister();
				oilLevel--;
			}else
			{
				isOilCanisterFull = true;
			}
		}	
	}

}

void ARefueler::FillUpLubricantCanister()
{
	if(lubricantCanister && !isLubricantCanisterFull)
	{
		if(lubricantLevel > 0)
		{
			if(lubricantCanister->GetCanisterCurrentLevel() < lubricantCanister->GetCanisterMaxCapacity())
			{
				lubricantCanister->FillCanister();
				lubricantLevel--;
			}else
			{
				isLubricantCanisterFull = true;
			}
		}
	}

}

// Method called to stop (if is used) oil Timer to refil Refueler Oil deposit.
void ARefueler::FillUpOilDeposit()
{
	oilLevel++;

}

// Method called to stop (if is used) Lubricant Timer to refil Refueler Lubricant deposit.
void ARefueler::FillUpLubricantDeposit()
{
	lubricantLevel++;

}

// Gets Oil Deposit Level.
int ARefueler::GetOilDepositLevel()
{
	return oilLevel;

}

// Get Lubricant Deposit Level.
int ARefueler::GetLubricantDepositLeve()
{
	return lubricantLevel;

}

// Gets MAX Oil Deposit Level.
int ARefueler::GetMaxOilDepositLevel()
{
	return maxOilCapacity;

}

// Get MAX Lubricant Deposit Level.
int ARefueler::GetMaxLubricantDepositLeve()
{
	return maxlubricantCapacity;

}
