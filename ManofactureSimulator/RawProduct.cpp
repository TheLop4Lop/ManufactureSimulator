// Fill out your copyright notice in the Description page of Project Settings.


#include "RawProduct.h"

// Sets default values
ARawProduct::ARawProduct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	productRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Raw Product Root"));
	RootComponent = productRootComponent;

	rawProductMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Raw Product Mesh"));
	rawProductMesh->SetupAttachment(productRootComponent);

}

// Called when the game starts or when spawned
void ARawProduct::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARawProduct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Sets product code based on initial BaseStorage struct.
void ARawProduct::SetProductCode(FInitialPieceAttribute productCode)
{
	productCodeProcess = productCode;

}

// Returns product codebased on initial BaseStorage struct.
FInitialPieceAttribute ARawProduct::GetProductCodeProcess()
{
	return productCodeProcess;

}

// Set Raw Product Mesh.
void ARawProduct::SetRawProductMesh(UStaticMesh* productMesh)
{
	rawProductMesh->SetStaticMesh(productMesh);

}

// Set Raw Product Size.
void ARawProduct::SetRawProductSize(FVector productSize)
{
	rawProductMesh->SetWorldScale3D(productSize);

}

// Set Raw Product Material.
void ARawProduct::SetRawProductMaterial(UMaterial* productMaterial)
{
	rawProductMesh->SetMaterial(0, productMaterial);
	
}
