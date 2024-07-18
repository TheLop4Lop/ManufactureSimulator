// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProduct.h"

// Sets default values
ABaseProduct::ABaseProduct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	productRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Raw Product Root"));
	RootComponent = productRootComponent;

	productMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Raw Product Mesh"));
	productMesh->SetupAttachment(productRootComponent);

}

// Called when the game starts or when spawned
void ABaseProduct::BeginPlay()
{
	Super::BeginPlay();

	productMesh->SetSimulatePhysics(true);
	productMesh->SetRenderCustomDepth(true);
	
}

// Called every frame
void ABaseProduct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Sets the mesh for the Product.
void ABaseProduct::SetsProductProperties(UStaticMesh* mesh, UMaterial* material, FVector size)
{
	productMesh->SetStaticMesh(mesh);
	productMesh->SetMaterial(0, material);
	productMaterial = material;

	productSize = size;
	productMesh->SetWorldScale3D(productSize);

}

//Gets the mesh of the product.
UStaticMesh* ABaseProduct::GetProductMesh()
{
	return productMesh->GetStaticMesh();

}

// Gets the material of the product.
UMaterial* ABaseProduct::GetProductMaterial()
{
	return productMaterial;

}

//Gets the size of the product.
FVector ABaseProduct::GetProductSize()
{
	return productSize;

}

// Set the quality of the piece, this depends on the type of proccess is being subimted to.
void ABaseProduct::SetProductQualityByProcess(float qualityByProcess)
{
	qualityPercent = qualityByProcess;

}

// Returns the quality of the piece.
float ABaseProduct::GetProductQuality()
{
	return qualityPercent;

}

// Sets cutted piece product code.
void ABaseProduct::SetProductCode(FString& code)
{
    productCode = code;

}

// Gets cutted piece product code.
FString& ABaseProduct::GetProductCode()
{
    return productCode;

}

void ABaseProduct::DestroyProduct()
{
	Destroy();

}
