// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseMachinery.generated.h"

UENUM(BlueprintType)
enum OrderCodes
{
	M1_S1,
	M1_S2,
	M1_S3,

	M2_S1,
	M2_S2,
	M2_S3,

	M3_S1,
	M3_S2,
	M3_S3,

	NoData_
};

UCLASS()
class MANOFACTURESIMULATOR_API ABaseMachinery : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseMachinery();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Widget related functions
	virtual void AddWidgetFromComputer(class ACharacterController* CharacterController);
	class TSubclassOf<class UUserWidget> GetComputerWidgetClass();

	void SetProductionOrder(FString Order);
	FString SetProductionOrderName(int Index);

	//Power machine
	void SetbIsPowered(bool bValue);
	bool IsPowered();

	//Productivity Get funtions
	int GetProductionCapacity();
	int GetRawPieces();
	int GetProducedPieces();

	//Maintinance mode machine
	void SetbInMaintenance(bool bValue);
	bool InMaintenance();

	virtual void NullWidgetTest();

protected:
	//UPROPERTY - Pawn Property
	UPROPERTY(EditAnywhere, Category = "Pawn Property", meta = (AllowPrivateAccess))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Pawn Property", meta = (AllowPrivateAccess))
	class UStaticMeshComponent* MachineComputerMesh;

	//UPROPERTY - MAchinary Property
	UPROPERTY(EditAnywhere, Category = "Widgets", meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> ComputerClass;
	class UMachineComputerWidget* ComputerWidget;

	UPROPERTY(EditAnywhere, Category = "Machinary Property", meta = (AllowPrivateAccess))
	bool bIsPowered;

	UPROPERTY(EditAnywhere, Category = "Machinary Property", meta = (AllowPrivateAccess))
	int ProductionCapacity;

	UPROPERTY(EditAnywhere, Category = "Machinary Property", meta = (AllowPrivateAccess))
	int RawPieces;

	UPROPERTY(EditAnywhere, Category = "Machinary Property", meta = (AllowPrivateAccess))
	int ProducedPieces;

	//UPROPERTY - Machinery Maintenance
	UPROPERTY(EditAnywhere, Category = "Machinary Maintenance", meta = (AllowPrivateAccess))
	bool bInMaintenance;

	UPROPERTY(EditAnywhere, Category = "Machinary Maintenance", meta = (AllowPrivateAccess))
	float MaintenanceTimeHold;

	//UPROPERTY - Machinary In Out properties
	UPROPERTY(EditAnywhere, Category = "Machinary Input/Output", meta = (AllowPrivateAccess))
	class UBoxComponent* BoxEntrance;

	UPROPERTY(EditAnywhere, Category = "Machinary Input/Output", meta = (AllowPrivateAccess))
	class UBoxComponent* BoxExit;

	//Spawn Product
	UPROPERTY(EditAnywhere, Category = "Piece", meta = (AllowPrivateAccess))
	TSubclassOf<class APiece> ProduceTypePiece;

	UPROPERTY(EditAnywhere, Category = "Actor Properties", meta = (AllowPrivateAccess))
	UStaticMesh* ProducedPieceMesh;//Posible change or new implementation

	//Spot Light
	UPROPERTY(EditAnywhere, Category = "Light Code", meta = (AllowPrivateAccess))
	class USpotLightComponent* SpotLight;

	//ConveyorBelts
	void FindConveyorBelt();
	class ABaseConveyorBelt* EntranceBelt;
	bool bDoOnceStopPower = true;
	bool bDoOnceStopConveyort = true;
	bool PieceCodeError;

	//Machinary In Out properties
	void HandleRawPiecesProduction();
	TArray<AActor*> ActorsEntrance;
	class APiece* Piece;
	class APiece* Product;

	//Timer Production
	FTimerHandle MachineTimer;
	float ProductionTime;

	//Maintenance
	void HandleMaintenanceMode();
	FTimerHandle MaintenanceTimer;
	void ExitMaintenanceMode();
	float MaintenanceHoldSeconds = 0;

	bool DoOnceMantenance = true;
	bool bControlMantenance = true;

	//Piece Properties
	class UPieceSpawnProperties* Properties;

	//Production
	void HandleCorrectOrder();

	virtual void RawPieceEntranceManager();
	virtual void GetEntrancePiece();
	virtual void ManageEntrancePiece();
	bool ShouldSpawnProducedPiece();
	virtual void ProducedPiecesExitManager();
	FVector SpawnProductLocation;

	void ActivateConveyortBelt();
	void StopConveyorBelt();

	int IdealPiecesPerMinute;
	int ActualPiecesPerMinute;

	FString OrderName; //Widget Related, Machine Configuration Widget Code
	int NoOrder; //Widget Related, Machine Configuration

	int PieceIndex;
	int HoldPieceIndex;
	FVector PieceSize;
	FString ProcessCode;

	OrderCodes ConverStringToEnum(FString ToConvert);

	//Control Bools
	bool DoOnce = true;
	bool DoMistake = false;

	//Color Process Code
	FColor ColorCode;

};
