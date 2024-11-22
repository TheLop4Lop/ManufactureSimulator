// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "EProductProperties.generated.h"

UENUM(BlueprintType)
enum class EPieceMaterial : uint8
{
	QUALITY_LOW,
	QUALITY_MEDIUM,
	QUALITY_HIGH
};

UENUM(BlueprintType)
enum class EPieceSize : uint8
{
	SIZE_SMALL,
	SIZE_MEDIUM,
	SIZE_BIG
};

UENUM(BlueprintType)
enum class EPieceLenght : uint8
{
	LENGTH_SHORT,
	LENGTH_MEDIUM,
	LENGTH_LARGE
};

UENUM(BlueprintType)
enum class EPieceForm : uint8
{
	FORM_CONE,
	FORM_CYLINDER,
	FORM_TORUS
};

UENUM(BlueprintType)
enum class EPieceColor : uint8
{
	COLOR_BLUE,
	COLOR_RED,
	COLOR_GREEN
};

/**
 * 
 */
UCLASS()
class MANOFACTURESIMULATOR_API UEProductProperties : public UUserDefinedEnum
{
	GENERATED_BODY()

public:
	///////////////////////////////////// CONVERT TO ENUMS ////////////////////////////////
	// Methods for convert FString to enum.

	// Retrieves a string and convert it into a EPieceMaterial enum.
	static EPieceMaterial ConverStringToEnumQuality(FString quality);

	// Retrieves a string and convert it into a EPieceSize enum.
	static EPieceSize ConverStringToEnumSize(FString size);

	// Retrieves a string and convert it into a EPieceLenght enum.
	static EPieceLenght ConverStringToEnumLength(FString length);

	// Retrieves a string and convert it into a EPieceForm enum.
	static EPieceForm ConverStringToEnumForm(FString form);

	// Retrieves a string and convert it into a EPieceColor enum.
	static EPieceColor ConverStringToEnumColor(FString color);
	
};
