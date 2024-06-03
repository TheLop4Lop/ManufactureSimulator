// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	Pawn = Cast<APawn>(GetOwner());
	Owner = Pawn->GetController();
	
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(GetPhysicsHandle() && IsGrabbing)
	{
		if(Owner != nullptr)
		{
			Owner->GetPlayerViewPoint(MoveLocation, MoveRotation);
		}

		FVector HeightCorrection = GetForwardVector() + FVector(0.f, 0.f, (MoveRotation.Vector().Z + 0.25f));
		FVector TargetLocation = GetComponentLocation() + (HeightCorrection * (MaxGrabDistance/2));

		GetPhysicsHandle()->SetTargetLocationAndRotation(TargetLocation, MoveRotation);
	}
	
}

void UGrabber::Grab()
{
	if(GetPhysicsHandle())
	{
		FHitResult HitResult;

		if(GrabObjectInReach(HitResult))
		{
			IsGrabbing = true;

			UPrimitiveComponent* HitComponent = HitResult.GetComponent();
			HitComponent->WakeAllRigidBodies();

			GetPhysicsHandle()->GrabComponentAtLocationWithRotation(
				HitComponent, 
				NAME_None, 
				HitResult.ImpactPoint,
				GetComponentRotation()
			);
		}

	}

}

void UGrabber::Release()
{	
	if(GetPhysicsHandle())
	{
		GetPhysicsHandle()->ReleaseComponent();
		IsGrabbing = false;
	}

}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle()
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(Result == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Nullptr, check code!"));
	}
	
	return Result;
	
}

bool UGrabber::GrabObjectInReach(FHitResult& HitResult) const
{
	FVector StartVector;
	FRotator ViewRotator;
	FVector EndVector;

	if(Owner != nullptr)
	{
		Owner->GetPlayerViewPoint(StartVector, ViewRotator);
		EndVector = StartVector + (ViewRotator.Vector() * MaxGrabDistance);
	}

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabSphereRadious);

	return GetWorld()->SweepSingleByChannel(
		HitResult, 
		StartVector, 
		EndVector, 
		FQuat::Identity, 
		ECC_GameTraceChannel2,
		Sphere
	);

}