// Fill out your copyright notice in the Description page of Project Settings.


#include "QualityComputer.h"
#include "Kismet/GameplayStatics.h"
#include "ComputerQualityWidget.h"
#include "CharacterController.h"
#include "MachineQuality.h"

// Static MATERIAL map for string to ENUM data, this is used for product interpretation in respective machine.
std::map<FString, EMaterial> AQualityComputer::StringToEnumMaterialMap;

// Static SIZE map for string to ENUM data, this is used for product interpretation in respective machine.
std::map<FString, ESize> AQualityComputer::StringToEnumSizeMap;

// Static FORM map for string to ENUM data, this is used for product interpretation in respective machine.
std::map<FString, EForm> AQualityComputer::StringToEnumFormMap;

// Static COLOR map for string to ENUM data, this is used for product interpretation in respective machine.
std::map<FString, EColor> AQualityComputer::StringToEnumColorMap;

AQualityComputer::AQualityComputer()
{
    if(StringToEnumMaterialMap.empty() && StringToEnumSizeMap.empty() && StringToEnumFormMap.empty() && StringToEnumColorMap.empty())
	{
		InitializeConversionMaps();
	}

}

void AQualityComputer::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> actorsInWorld;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(),AMachineQuality::StaticClass(), actorsInWorld);
    if(actorsInWorld.IsValidIndex(0)) qualityMachine = Cast<AMachineQuality>(actorsInWorld[0]);

}

// Called every frame
void AQualityComputer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(qualityMachine && computerWidget)
    {
		computerWidget->SetMachinePowerStatus(qualityMachine->GetMachinePower());
		computerWidget->SetPowerLight(qualityMachine->GetMachinePower());

        computerWidget->SetProductMaterial(materialQuality);
		computerWidget->SetProductSize(materialSize);
		computerWidget->SetProductForm(materialForm);
		computerWidget->SetProductColor(materialColor);
		computerWidget->SetProductLastProccess(materialLastProccess);

		computerWidget->SetProductActualQuality(productActualQuality/100);
		computerWidget->SetProducExpectedQuality(productExpectedQuality/100);
    }

}

///////////////////////////////////// MAP CONVERTION ////////////////////////////////
// Singleton implementation for String-ENUM convertion, this help to all child classes access to transformation.

void AQualityComputer::InitializeConversionMaps()
{
	StringToEnumMaterialMap = {{"M1", EMaterial::M1}, {"M2", EMaterial::M2}, {"M3", EMaterial::M3}};

	StringToEnumSizeMap = {{"S1", ESize::S1}, {"S2", ESize::S2}, {"S3", ESize::S3}};

	StringToEnumFormMap = {{"F1", EForm::F1}, {"F2", EForm::F2}, {"F3", EForm::F3}};

	StringToEnumColorMap = {{"C1", EColor::C1}, {"C2", EColor::C2}, {"C3", EColor::C3}};

}

// Gets the StringToEnumMaterialMap
EMaterial AQualityComputer::GetStringToEnumMaterialMap(const FString& materialString) const
{
	auto it = StringToEnumMaterialMap.find(materialString);
	if(it != StringToEnumMaterialMap.end())
	{
		return it->second;
	}

	return EMaterial::M1;

}

// Gets the StringToEnumSizeMap
ESize AQualityComputer::GetStringToEnumSizeMap(const FString& sizeString) const
{
	auto it = StringToEnumSizeMap.find(sizeString);
	if(it != StringToEnumSizeMap.end())
	{
		return it->second;
	}

	return ESize::S1;

}

// Gets the StringToEnumFormMap
EForm AQualityComputer::GetStringToEnumFormMap(const FString& formString) const
{
	auto it = StringToEnumFormMap.find(formString);
	if(it != StringToEnumFormMap.end())
	{
		return it->second;
	}

	return EForm::F1;

}

// Gets the StringToEnumColorMap
EColor AQualityComputer::GetStringToEnumColorMap(const FString& colorString) const
{
	auto it = StringToEnumColorMap.find(colorString);
	if(it != StringToEnumColorMap.end())
	{
		return it->second;
	}

	return EColor::C1;

}

// Adds widget and assign the player controller to it.
void AQualityComputer::AddWidgetFromComputer(ACharacterController* CharacterController)
{
	characterController = CharacterController;
	computerWidget = Cast<UComputerQualityWidget>(CreateWidget(characterController, computerClass));

	if(computerWidget)
	{
		computerWidget->AddToViewport();
		computerWidget->exitButtonEvent.BindUObject(this, &ABaseComputer::PublicWidgetBindResetController);

        computerWidget->powerAction.BindUObject(this, &AQualityComputer::SetPowerStatus);
        computerWidget->scanAction.BindUObject(this, &AQualityComputer::ScanProductAction);
	}

}

///////////////////////////////////// BASE COMPUTER PROPERTIES ////////////////////////////////
// Sections for the actor properties.

// Resets the character controller to move the character around.
void AQualityComputer::WidgetBindResetController()
{
    characterController->SetMovement(false);
	characterController = nullptr;
    
    computerWidget = nullptr;

}

///////////////////////////////////// MACHINE COMPUTER PROPERTIES ////////////////////////////////
// Sections for the actor properties.

// Changes Machine Power Status.
void AQualityComputer::SetPowerStatus()
{
    if(qualityMachine)
    {
        qualityMachine->SetMachinePower();
    }

}

// Calls scann product interaction.
void AQualityComputer::ScanProductAction()
{
    if(qualityMachine)
    {
		switch (qualityMachine->ScanForProduct())
		{
		case EMachineQualityStatus::POWER_OFF:
			break;

		case EMachineQualityStatus::BOX_EMPTY:
			if(computerWidget) UE_LOG(LogTemp, Display, TEXT("PLACE A PRODUCTION PRODUCT ON THE SCANNER."));
			break;

		case EMachineQualityStatus::NO_MATCH:
			if(computerWidget) UE_LOG(LogTemp, Display, TEXT("OBJECT IN THE SCANNER NOT MATCH A PRODUCTION PRODUCT."));
			break;

		case EMachineQualityStatus::MULTIPLE:
			if(computerWidget) UE_LOG(LogTemp, Display, TEXT("REMOVE ITEMS, ONLY ONE PRODUCTIO PRODUCT ON THE SCANNER."));
			break;
		
		case EMachineQualityStatus::SCANNED:
			ReadProductProperties(qualityMachine->GetProductCode());
			ReadProductQuality(qualityMachine->GetProductQuality());
			break;
		
		default:
			break;
		}
    }

}

// Read Product Properties.
void AQualityComputer::ReadProductProperties(FString productCode)
{
	UE_LOG(LogTemp, Display, TEXT("PRODUCT PROPESTIES SCANNER: %s"), *productCode);
	GetMaterialCodeSetMaterialQuality(productCode.Left(2));

	if(productCode.Len() == 4)
	{
		GetSizeCodeSetMaterialSize(productCode.Right(2)); // Gets Sx if it's on this format: Mx Sx.
		materialLastProccess = TEXT("Cutter Machine Proccess");
		materialForm = TEXT(" - ");
		materialColor = TEXT(" - ");
	}else if(productCode.Len() > 4)
	{
		GetSizeCodeSetMaterialSize(productCode.Mid(2, 2)); // Gets Sx if it's on this format: MxSxLx, MxSxFx or MxSxFxCx.

		if(productCode.Len() < 8)
		{
			// Checks if productCode has format: Mx Sx Fx.
			if(productCode[4] == 'F')
			{
				GetFormCodeSetMaterialForm(productCode.Right(2)); // Gets Fx if it's on this format: MxSxFx.
				materialLastProccess = TEXT("Molder Machine Proccess");
				materialColor = TEXT(" - ");
			}else
			{
				materialLastProccess = TEXT("Fresh Raw Material");
				materialForm = TEXT(" - ");
				materialColor = TEXT(" - ");
			}
		}else if(productCode.Len() == 8)
		{	
			UE_LOG(LogTemp, Display, TEXT("productCode Lenght: %i"), productCode.Len());

			materialLastProccess = TEXT("Painter Machine Proccess");
			GetFormCodeSetMaterialForm(productCode.Mid(4, 2)); // Gets Fx if it's on this format: MxSxFxCx.
			GetColorCodeSetMaterialColor(productCode.Right(2)); // Gets Fx on this format: MxSxFxCx.
		}
	}
	
}

// Read Product Quality.
void AQualityComputer::ReadProductQuality(float productQuality)
{
	productActualQuality = productQuality;

}

// Set product materialQuality.
void AQualityComputer::GetMaterialCodeSetMaterialQuality(FString materialCode)
{
	// Gets Mx no Matter the size of the materialCode.
	switch (GetStringToEnumMaterialMap(materialCode))
	{
	case EMaterial::M1:
		materialQuality = TEXT("M1 - Low Quality Material.");
		productExpectedQuality = 40.0;
		break;

	case EMaterial::M2:
		materialQuality = TEXT("M2 - Medium Quality Material.");
		productExpectedQuality = 70.0;
		break;

	case EMaterial::M3:
		materialQuality = TEXT("M3 - High Quality Material.");
		productExpectedQuality = 100.0;
		break;
	
	default:
		break;
	}

}

// Set product materialSize.
void AQualityComputer::GetSizeCodeSetMaterialSize(FString sizeCode)
{
	switch (GetStringToEnumSizeMap(sizeCode))
	{
	case ESize::S1:
		materialSize = TEXT("S1 - Small Size Material.");
		break;

	case ESize::S2:
		materialSize = TEXT("S2 - Medium Size Material.");
		break;

	case ESize::S3:
		materialSize = TEXT("S3 - Big Size Material.");
		break;
	
	default:
		break;
	}

}

// Set product materialForm.
void AQualityComputer::GetFormCodeSetMaterialForm(FString formCode)
{
	switch (GetStringToEnumFormMap(formCode))
	{
	case EForm::F1:
		materialForm = TEXT("F1 - Cone Form Product.");
		break;

	case EForm::F2:
		materialForm = TEXT("F2 - Cylinder Form Product.");
		break;

	case EForm::F3:
		materialForm = TEXT("F3 - Torus Form Product.");
		break;
	
	default:
		break;
	}

}

// Set product materialColor.
void AQualityComputer::GetColorCodeSetMaterialColor(FString colorCode)
{
	switch (GetStringToEnumColorMap(colorCode))
	{
	case EColor::C1:
		materialColor = TEXT("C1 - Blue Color Product.");
		break;

	case EColor::C2:
		materialColor = TEXT("C2 - Red Color Product.");
		break;

	case EColor::C3:
		materialColor = TEXT("C3 - Green Color Product.");
		break;
	
	default:
		break;
	}

}
