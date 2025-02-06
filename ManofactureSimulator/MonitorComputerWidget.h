// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "MonitorComputerWidget.generated.h"

USTRUCT(BlueprintType)
struct FOrderOTD
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FColor orderColorStatus = FColor::FromHex("141414FF");

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int canProduceByStock = 0;

	int lxProperties[3];

};

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UMonitorComputerWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	// Method to recieve data from player to show information on widget.
	void SetOrderOTDsStatus(TArray<FString> ordersOTD, TArray<FOrderOTD> ordersOTDStatus);

	// Set the amount of money produced by the factory.
	void SetEarnings(float money);

protected:
	///////////////////////////////////// DISPLAY ORDER STATUS PROPERTIES ////////////////////////////////
	// Section for display orders.

	// Image to change color indicator of aviability on stock based on index.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* ImageIndex0;

	// Image to change color indicator of aviability on stock based on index.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* ImageIndex1;

	// Image to change color indicator of aviability on stock based on index.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* ImageIndex2;

	// Image to change color indicator of aviability on stock based on index.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* ImageIndex3;

	// Image to change color indicator of aviability on stock based on index.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* ImageIndex4;

	// Image to change color indicator of aviability on stock based on index.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* ImageIndex5;

	//

	// Text block for name order based on index.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* orderIndex0;

	// Text block for name order based on index.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* orderIndex1;

	// Text block for name order based on index.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* orderIndex2;

	// Text block for name order based on index.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* orderIndex3;

	// Text block for name order based on index.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* orderIndex4;

	// Text block for name order based on index.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* orderIndex5;

	//

	// Text block for max producion of order on stock.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* stockIndex0;

	// Text block for max producion of order on stock.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* stockIndex1;

	// Text block for max producion of order on stock.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* stockIndex2;

	// Text block for max producion of order on stock.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* stockIndex3;

	// Text block for max producion of order on stock.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* stockIndex4;

	// Text block for max producion of order on stock.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* stockIndex5;

	//

	// Text block for l1 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l1Index0;

	// Text block for l1 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l1Index1;

	// Text block for l1 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l1Index2;

	// Text block for l1 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l1Index3;

	// Text block for l1 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l1Index4;

	// Text block for l1 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l1Index5;

	//

	// Text block for l2 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l2Index0;

	// Text block for l2 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l2Index1;

	// Text block for l2 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l2Index2;

	// Text block for l2 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l2Index3;

	// Text block for l2 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l2Index4;

	// Text block for l2 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l2Index5;

	//

	// Text block for l3 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l3Index0;

	// Text block for l3 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l3Index1;

	// Text block for l3 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l3Index2;

	// Text block for l3 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l3Index3;

	// Text block for l3 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l3Index4;

	// Text block for l3 quantity based on index order.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* l3Index5;

	///////////////////////////////////// DISPLAY MONEY STATUS PROPERTIES ////////////////////////////////
	// Section for display money.
	
	// Holds the Value of the Current Money.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* playerMoney;

};
