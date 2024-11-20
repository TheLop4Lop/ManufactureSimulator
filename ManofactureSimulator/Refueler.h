// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Refueler.generated.h"

UCLASS()
class MANOFACTURESIMULATOR_API ARefueler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARefueler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called frm Refueler Computer after widget Power interactio; change status between ON and OFF.
	void SetMachinePower();

	// Gets power status for widget interaction.
	bool GetMachinePower();

	// Called from Refueler Computer after widget Security DOOR interaction; Open or Close Security Door.
	void SecurityDoorChangePosition();

	// Called from Refueler Computer after widget OIL interaction, if Service door is closed return true, otherwise false.
	bool OilActionButton();

	// Called from Refueler Computer after widget LUBRICANT interaction, if Service door is closed return true, otherwise false.
	bool LubricantActionButton();

	// Called from Manager Computer to fill Oil Deposit.
	void FillOilDepositAction();

	// Called from Manager Computer to fill Lubricant Deposit.
	void FillLubricantDepositAction();

	// Gets Oil Deposit Level.
	int GetOilDepositLevel();

	// Get Lubricant Deposit Level.
	int GetLubricantDepositLeve();

	// Gets MAX Oil Deposit Level.
	int GetMaxOilDepositLevel();

	// Get MAX Lubricant Deposit Level.
	int GetMaxLubricantDepositLeve();

protected:
	///////////////////////////////////// REFUELER PROPERTIES ////////////////////////////////
	// Sections for the actor properties.

	// Refueler mesh reference.
	UPROPERTY(EditAnywhere, Category = "Refueler Properties", meta = (AllowPrivateAccess))
	USceneComponent* refuelerRoot;

	// Refueler mesh reference.
	UPROPERTY(EditAnywhere, Category = "Refueler Properties", meta = (AllowPrivateAccess))
	UStaticMeshComponent* refuelerMesh;

	// Refueler segurity Door.
	UPROPERTY(EditAnywhere, Category = "Refueler Properties", meta = (AllowPrivateAccess))
	UStaticMeshComponent* refuelerDoor;

	// Box component to detect individual oil canisterBox to fill it up.
	UPROPERTY(EditAnywhere, Category = "Refueler Properties", meta = (AllowPrivateAccess))
	class UBoxComponent* oilCanisterBox;

	// Box component to detect individual lubricant lubricantBox to fill it up.
	UPROPERTY(EditAnywhere, Category = "Refueler Properties", meta = (AllowPrivateAccess))
	class UBoxComponent* lubricantCanisterBox;

	// Reference to specific oilCanister.
	class AOilCanister* oilCanister;

	// Reference to specific lubricantCanister.
	class ALubricantCanister* lubricantCanister;

	///////////////////////////////////// REFUELER STATUS ////////////////////////////////
	// Section for Refueler status reflects the actual stages of the refueler.

	// Sets if Refueler is On or Off.
	UPROPERTY(EditAnywhere, Category = "Refueler Status", meta = (AllowPrivateAccess))
	bool bIsPowered;

	// Sets the status of security door for process controll.
	UPROPERTY(EditAnywhere, Category = "Refueler Status", meta = (AllowPrivateAccess))
	bool bIsDoorOpen;

	// Sets if Refueler oil deposit is being filled.
	UPROPERTY(EditAnywhere, Category = "Refueler Status", meta = (AllowPrivateAccess))
	bool bOilDepositBeingilled;

	// Sets if Refueler lubricant deposit is being filled.
	UPROPERTY(EditAnywhere, Category = "Refueler Status", meta = (AllowPrivateAccess))
	bool blubricantDepositBeingilled;

	// Sets if OilCanister is full.
	UPROPERTY(EditAnywhere, Category = "Refueler Status", meta = (AllowPrivateAccess))
	bool isOilCanisterFull;

	// Sets if LubricantCanister is full.
	UPROPERTY(EditAnywhere, Category = "Refueler Status", meta = (AllowPrivateAccess))
	bool isLubricantCanisterFull;

	///////////////////////////////////// REFUELER PROCESS ////////////////////////////////
	// Section for Refueler fill canisters process.

	// Holds the max value of the Oil deposit.
	UPROPERTY(EditAnywhere, Category = "Refueler Process", meta = (AllowPrivateAccess))
	int maxOilCapacity = 200;

	// Holds the value of the actual oil deposit level.
	UPROPERTY(EditAnywhere, Category = "Refueler Process", meta = (AllowPrivateAccess))
	int oilLevel;

	// Holds the max value of the lubricant deposit.
	UPROPERTY(EditAnywhere, Category = "Refueler Process", meta = (AllowPrivateAccess))
	int maxlubricantCapacity = 200;

	// Holds the value of the actual lubricant deposit level.
	UPROPERTY(EditAnywhere, Category = "Refueler Process", meta = (AllowPrivateAccess))
	int lubricantLevel;

	// Hods the value of the time to fill one unity of oil into the Refueler Deposit.
	UPROPERTY(EditAnywhere, Category = "Refueler Process", meta = (AllowPrivateAccess))
	float oilDepositFillUpTime = 0.5f;

	// Hods the value of the time to fill one unity of lubricant into the Refueler Deposit.
	UPROPERTY(EditAnywhere, Category = "Refueler Process", meta = (AllowPrivateAccess))
	float lubricantDepositFillUpTime = 0.2f;

	// Hods the value of the time to fill one unity of oil into the canister.
	UPROPERTY(EditAnywhere, Category = "Refueler Process", meta = (AllowPrivateAccess))
	float oilCanisterFillUpTime = 1.5f;

	// Hods the value of the time to fill one unity of lubricant into the canister.
	UPROPERTY(EditAnywhere, Category = "Refueler Process", meta = (AllowPrivateAccess))
	float lubricantCanisterFillUpTime = 1.0f;

	// Handles timer for oil Deposit fill up.
	FTimerHandle oilDepositTimer;

	// Handles timer for lubricant Deposit fill up.
	FTimerHandle lubricantDepositTimer;

	// Search for actors in oilCanisterBox and manages the filling main logic.
	void CheckOilBoxForActorsAction();

	// Search for actors in lubricantCanisterBox and manages the filling main logic.
	void CheckLubricantBoxForActorsAction();

	// Method called from a timer, manages Oil Canister fill up.
	UFUNCTION()
	void FillUpOilCanister();

	// Method called from a timer, manages Lubricant Canister fill up.
	UFUNCTION()
	void FillUpLubricantCanister();

	// Method called to stop (if is used) oil Timer to refil Refueler Oil deposit.
	UFUNCTION()
	void FillUpOilDeposit();

	// Method called to stop (if is used) Lubricant Timer to refil Refueler Lubricant deposit.
	UFUNCTION()
	void FillUpLubricantDeposit();

	// Controls flow on clear oil timer Process.
	bool DoOnceOil;

	// Controls flow on clear lubricant timer Process.
	bool DoOnceLubricant;

	///////////////////////////////////// REFUELER SOUNDS ////////////////////////////////
	// Section for Refueler sounds.

	// Holds the reference to a SoundBase for PowerOn machine.
	UPROPERTY(EditAnywhere, Category = "Refueler Sounds", meta = (AllowPrivateAccess))
	USoundBase* refuelerOnSound;

	// Holds the reference to a SoundBase for missingCanister on plaque machine.
	UPROPERTY(EditAnywhere, Category = "Refueler Sounds", meta = (AllowPrivateAccess))
	USoundBase* missingCanisterSound;

	// Holds the reference to a SoundBase for wrong object on plaque machine.
	UPROPERTY(EditAnywhere, Category = "Refueler Sounds", meta = (AllowPrivateAccess))
	USoundBase* wrongCanisterSound;

	// Holds the reference to a SoundBase for Open door warning on plaque machine.
	UPROPERTY(EditAnywhere, Category = "Refueler Sounds", meta = (AllowPrivateAccess))
	USoundBase* openDoorWarningSound;

	// Holds the reference to a SoundBase for actionDoor sound on plaque machine.
	UPROPERTY(EditAnywhere, Category = "Refueler Sounds", meta = (AllowPrivateAccess))
	USoundBase* actionDoorSound;

	// Holds the reference to a SoundBase for oil refuil sound.
	UPROPERTY(EditAnywhere, Category = "Refueler Sounds", meta = (AllowPrivateAccess))
	USoundBase* refuelerOilSound;

	// Holds the reference to a SoundBase for lubricant refuil sound.
	UPROPERTY(EditAnywhere, Category = "Refueler Sounds", meta = (AllowPrivateAccess))
	USoundBase* refuelerLubricantSound;

	// Handles On audio Spawned in the world.
	class UAudioComponent* onAudioHandle;

	// Handles Oil audio Spawned in the world.
	class UAudioComponent* oilAudioHandle;

	// Handles Lubricant audio Spawned in the world.
	class UAudioComponent* lubricantAudioHandle;

};
