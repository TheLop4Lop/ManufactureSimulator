// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalStorage.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"
//#include "Piece.h"

// Sets default values
AFinalStorage::AFinalStorage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFinalStorage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinalStorage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
