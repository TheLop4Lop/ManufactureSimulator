// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MANOFACTURESIMULATOR_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class UPhysicsHandleComponent* GetPhysicsHandle();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

private:
	UPROPERTY(EditAnywhere, Category = "Component Settings", meta = (AllowPrivateAccess = "True"))
	float MaxGrabDistance = 400;
	
	//Defines the radious of the sphere collision
	UPROPERTY(EditAnywhere, Category = "Component Settings", meta = (AllowPrivateAccess = "True"))
	float GrabSphereRadious;

	UPROPERTY(EditAnywhere, Category = "Component Settings", meta = (AllowPrivateAccess = "True"))
	FVector GrabberModifier = FVector(0, 0, 20);

	//Returns if the collision sphere hit with an object or not
	bool GrabObjectInReach(FHitResult& HitResult) const;

	APawn* Pawn;
	AController* Owner;

	FVector MoveLocation;
	FRotator MoveRotation;

	bool IsGrabbing;

};
