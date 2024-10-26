// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProduct.generated.h"

UCLASS()
class MANOFACTURESIMULATOR_API ABaseProduct : public AActor, public IInteractable
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
	void SetProductQuality(int qualityByProcess);
	// Returns the quality of the piece.
	int GetProductQuality();

	// Sets cutted piece product code.
	void SetProductCode(FString& code);
	// Gets cutted piece product code.
	FString& GetProductCode();

	// Method implementation after character interaction, change canister properties for character hold.
	virtual void InteractionFunctionality_Implementation() override;

	// Destroys the product.
	void DestroyProduct();

protected:
	///////////////////////////////////// BASE PRODUCT PROPERTIES ////////////////////////////////
	// Section for the product properties, this interact with the respective machine class.

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
	int qualityPercent;

	// Holds the status for product ready for final storage.
	UPROPERTY(EditAnywhere, Category = "Product Properties", meta = (AllowPrivateAccess))
	bool bProductFinished;

	// Stores product code to be readed by the next machine in the process.
	FString productCode;
	
	// Changes the finish product status
	void SetProductFinishProduction();

	///////////////////////////////////// BASE PRODUCT INTERACTION ////////////////////////////////
	// Section for Base Product interaction with character.

	// Restets the behaviour of the mesh to it's original state.
	UFUNCTION()
	void SetProductReleaseReset();

	// Restets the behaviour of the mesh to it's original state and set location to a specific location.
	UFUNCTION()
	void SetProductComplexReleaseReset(UPrimitiveComponent* hitComponent);

	// Holds reference to character for canister event reset.
	class ABaseCharacter* character;

};
