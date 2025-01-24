// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProduct.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"

// Sets default values
ABaseProduct::ABaseProduct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	productMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Raw Product Mesh"));
	RootComponent = productMesh;

	productMesh->OnComponentHit.AddDynamic(this, &ABaseProduct::HitSound);

}

// Called when the game starts or when spawned
void ABaseProduct::BeginPlay()
{
	Super::BeginPlay();

	bProductFinished = false;

	productMesh->SetSimulatePhysics(true);
	productMesh->SetRenderCustomDepth(true);
	productMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	productMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	productMesh->SetNotifyRigidBodyCollision(true);

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
void ABaseProduct::SetProductQuality(int initialQuality)
{
	qualityPercent = initialQuality;

}

// Returns the quality of the piece.
int ABaseProduct::GetProductQuality()
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

// Returns the state of product finished.
bool ABaseProduct::IsProductFinished()
{
	return bProductFinished;

}

// Changes the finish product status
void ABaseProduct::SetProductFinishProduction()
{
	bProductFinished = true;

}

void ABaseProduct::DestroyProduct()
{
	Destroy();

}

///////////////////////////////////// BASE PRODUCT INTERACTION ////////////////////////////////
// Section for Base Product interaction with character.

// IInteractable interface method for character interaction.
void ABaseProduct::InteractionFunctionality_Implementation()
{
	productMesh->SetSimulatePhysics(false);
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if(character)
	{
		character->releaseHold.BindUObject(this, &ABaseProduct::SetProductReleaseReset);
		character->releaseComplexHold.BindUObject(this, &ABaseProduct::SetProductComplexReleaseReset);
	}

}

void ABaseProduct::SetProductReleaseReset()
{
	productMesh->SetSimulatePhysics(true);

	character = nullptr;
	
}

// Restets the behaviour of the mesh to it's original state and set location to a specific location.
void ABaseProduct::SetProductComplexReleaseReset(UPrimitiveComponent* hitComponent)
{
	if(hitComponent)
	{
		FVector boxLocation = hitComponent->GetComponentLocation();
		productReleasedOnComponentSound = LoadObject<USoundBase>(nullptr, TEXT("SoundCue'/Game/Sounds/Pieces/Piece_Cue2.Piece_Cue2'"));
		if(productReleasedOnComponentSound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), productReleasedOnComponentSound, boxLocation);

		AttachToComponent(hitComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SetActorLocation(boxLocation);
		productMesh->SetSimulatePhysics(true);

		character = nullptr;
	}

}

void ABaseProduct::HitSound(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	float volumeMultiplier = FMath::Clamp(NormalImpulse.Size() / MaxImpulse, 0.0f, 2.0f);
	productReleasedFreeSound = LoadObject<USoundBase>(nullptr, TEXT("SoundCue'/Game/Sounds/Pieces/Piece_Cue3.Piece_Cue3'"));
	if(productReleasedFreeSound && volumeMultiplier > 0.06)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), productReleasedFreeSound, GetActorLocation(), volumeMultiplier);
	}

}
