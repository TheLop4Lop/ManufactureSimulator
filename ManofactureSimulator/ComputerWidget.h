// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ComputerWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UComputerWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int InitialPieceQuantity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LenghtName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MaterialName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SizeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString OrderName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UImage* ErrorLed;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UTextBlock* OrdersTextBlock;

    void UpdateOrdersTextBlock(const TArray<FString> StringArray);
	void SetBaseComputer(class ABaseComputer* NewComputer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int L1Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int L2Quantity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int L3Quantity;

private:
	class ABaseCharacter* Character;
	class ABaseComputer* Computer;

	//Increment or decrement Order quantity
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* IncrementButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* DecrementButton;

	void SetQuantityButtons();

	UFUNCTION()
	void IncrementButtonClick();

	UFUNCTION()
	void DecrementButtonClick();

	//Initial Piece Lenght
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* L1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* L2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* L3;

	void SetLenghtButtons();

	UFUNCTION()
	void L1ButtonClick();

	UFUNCTION()
	void L2ButtonClick();

	UFUNCTION()
	void L3ButtonClick();

	//Material Type
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* M1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* M2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* M3;

	void SetMaterialButtons();

	UFUNCTION()
	void M1ButtonClick();

	UFUNCTION()
	void M2ButtonClick();

	UFUNCTION()
	void M3ButtonClick();

	//Material Size
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* S1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* S2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* S3;

	void SetSizeButtons();

	UFUNCTION()
	void S1ButtonClick();

	UFUNCTION()
	void S2ButtonClick();

	UFUNCTION()
	void S3ButtonClick();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ConfirmButton;

	void SetConfirmExitButtons();

	UFUNCTION()
	void ConfirmButtonClick();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ExitButton;

	UFUNCTION()
	void ExitButtonClick();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* RefeshButton;

	void SetRefreshButtonClick();

	UFUNCTION()
	void RefreshButtonClick();

	TArray<FString>* ArrayOrdersToProduct;
	TArray<FString> TemporaryProducts;
	bool OrderError;
	
};
