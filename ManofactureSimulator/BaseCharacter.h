// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class MANOFACTURESIMULATOR_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void ResetMoveInput();

private:
	UPROPERTY(EditAnywhere, Category = "Character Properties", meta = (AllowPrivateAccess))
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Character Properties", meta = (AllowPrivateAccess))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Character Properties", meta = (AllowPrivateAccess))
	float ObjectRangeSight = 100;

	UPROPERTY(EditAnywhere, Category = "Widgets", meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> InteractionWidgetClass;
	UUserWidget* InteractionWidget;

	class ABaseComputer* Computer;
	class ABaseMachinery* ComputerMachine;

	class ACharacterController* CharacterController;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Interaction();

	AActor* InSightLine();
	bool DoOnceWidget = true;

};
