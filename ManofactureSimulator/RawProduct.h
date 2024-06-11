// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseStorage.h"
#include "RawProduct.generated.h"

UCLASS()
class MANOFACTURESIMULATOR_API ARawProduct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARawProduct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets product code based on initial BaseStorage struct.
	void SetProductCode(FInitialPieceAttribute productCode);
	// Returns product codebased on initial BaseStorage struct.
	struct FInitialPieceAttribute GetProductCodeProcess();

	// Set Raw Product Mesh.
	void SetRawProductMesh(UStaticMesh* productMesh);
	// Set Raw Product Size.
	void SetRawProductSize(FVector productSize);
	// Set Raw Product Material.
	void SetRawProductMaterial(UMaterial* productMaterial);

private:
	///////////////////////////////////// PRODUCT PROPERTIES ////////////////////////////////
	// Product base properties.

	// Product root component.
	UPROPERTY(EditAnywhere, Category = "Product Properties", meta = (AllowPrivateAccess))
	USceneComponent* productRootComponent;

	// Product Static Mesh Component.
	UPROPERTY(EditAnywhere, Category = "Product Properties", meta = (AllowPrivateAccess))
	UStaticMeshComponent* rawProductMesh;

	// Product Material.
	UPROPERTY(EditAnywhere, Category = "Product Properties", meta = (AllowPrivateAccess))
	UMaterial* rawProductMaterial;

	// Holds struct of product code.
	FInitialPieceAttribute productCodeProcess;

};
