// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProduct.generated.h"

UCLASS()
class MANOFACTURESIMULATOR_API ABaseProduct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProduct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets the mesh for the Product.
	void SetsProductProperties(UStaticMesh* mesh, UMaterial* material, FVector size);
	//Gets the mesh of the product.
	UStaticMesh* GetProductMesh();
	// Gets the material of the product.
	UMaterial* GetProductMaterial();
	//Gets the size of the product.
	FVector GetProductSize();

	// Set the quality of the piece, this depends on the type of proccess is being subimted to.
	void SetProductQualityByProcess(float qualityByProcess);
	// Returns the quality of the piece.
	float GetProductQuality();

	// Destroys the product.
	void DestroyProduct();

protected:
	///////////////////////////////////// BASE PRODUCT PROPERTIES ////////////////////////////////
	// Section for the product properties, this interact with the respective machine class.

	// Product root component.
	UPROPERTY(EditAnywhere, Category = "Product Properties", meta = (AllowPrivateAccess))
	USceneComponent* productRootComponent;

	// Product Static Mesh
	UPROPERTY(EditAnywhere, Category = "Product Properties", meta = (AllowPrivateAccess))
	UStaticMeshComponent* productMesh;

	// Product Material.
	UPROPERTY(EditAnywhere, Category = "Product Properties", meta = (AllowPrivateAccess))
	UMaterial* productMaterial;

	// Product Size.
	UPROPERTY(EditAnywhere, Category = "Product Properties", meta = (AllowPrivateAccess))
	FVector productSize;

	// Holds the quality of the piece.
	UPROPERTY(EditAnywhere, Category = "Product Properties", meta = (AllowPrivateAccess))
	float qualityPercent;

};