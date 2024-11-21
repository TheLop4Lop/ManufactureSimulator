// Fill out your copyright notice in the Description page of Project Settings.


#include "EProductProperties.h"

#include <map>
#include <string>

// Singleton - Static method that returns a single QualityMap instance.
static const std::map<std::string, EPieceMaterial>& GetQualityMap()
{
	static const std::map<std::string, EPieceMaterial> tableQuality = { 
		{"M1", EPieceMaterial::QUALITY_LOW}, 
		{"M2", EPieceMaterial::QUALITY_MEDIUM},  
		{"M3", EPieceMaterial::QUALITY_HIGH}};

	return tableQuality;

}

// Singleton - Static method that returns a single GetSizeMap instance.
static const std::map<std::string, EPieceSize>& GetSizeMap()
{
	static const std::map<std::string, EPieceSize> tableSize = { 
		{"S1",EPieceSize::SIZE_SMALL},
		{"S2",EPieceSize::SIZE_MEDIUM},
		{"S3",EPieceSize::SIZE_BIG}};

	return tableSize;
}

// Singleton - Static method that returns a single GetLengthMap instance.
static const std::map<std::string, EPieceLenght>& GetLengthMap()
{
	static const std::map<std::string, EPieceLenght> tableLength = { 
		{"L1",EPieceLenght::LENGTH_SHORT},
		{"L2",EPieceLenght::LENGTH_MEDIUM},
		{"L3",EPieceLenght::LENGTH_LARGE}};

	return tableLength;
}

// Singleton - Static method that returns a single GetSizeMap instance.
static const std::map<std::string, EPieceForm>& GetFormMap()
{
	static const std::map<std::string, EPieceForm> tableSize = { 
		{"F1",EPieceForm::FORM_CONE},
		{"F2",EPieceForm::FORM_CYLINDER},
		{"F3",EPieceForm::FORM_TORUS}};

	return tableSize;
}

// Singleton - Static method that returns a single GetLengthMap instance.
static const std::map<std::string, EPieceColor>& GetColorMap()
{
	static const std::map<std::string, EPieceColor> tableLength = { 
		{"C1",EPieceColor::COLOR_BLUE},
		{"C2",EPieceColor::COLOR_RED},
		{"C3",EPieceColor::COLOR_GREEN}};

	return tableLength;
}

///////////////////////////////////// CONVERT TO ENUMS ////////////////////////////////
// Methods for convert FString to enum.

// Retrieves a string and convert it into a EPieceMaterial enum.
EPieceMaterial UEProductProperties::ConverStringToEnumQuality(FString quality)
{
	std::string order = std::string(TCHAR_TO_UTF8(*quality));
	auto& tableQuality = GetQualityMap();
	auto iTable = tableQuality.find(order);
	
	return (iTable != tableQuality.end()) ? iTable->second : EPieceMaterial::QUALITY_LOW;

}

// Retrieves a string and convert it into a EPieceSize enum.
EPieceSize UEProductProperties::ConverStringToEnumSize(FString size)
{
	std::string order = std::string(TCHAR_TO_UTF8(*size));
	auto& tableQuality = GetSizeMap();
	auto iTable = tableQuality.find(order);
	
	return (iTable != tableQuality.end()) ? iTable->second : EPieceSize::SIZE_SMALL;

}

// Retrieves a string and convert it into a EPieceLenght enum.
EPieceLenght UEProductProperties::ConverStringToEnumLength(FString length)
{
	std::string order = std::string(TCHAR_TO_UTF8(*length));
	auto& tableQuality = GetLengthMap();
	auto iTable = tableQuality.find(order);
	
	return (iTable != tableQuality.end()) ? iTable->second : EPieceLenght::LENGTH_SHORT;

}

// Retrieves a string and convert it into a EPieceForm enum.
EPieceForm UEProductProperties::ConverStringToEnumForm(FString form)
{
	std::string order = std::string(TCHAR_TO_UTF8(*form));
	auto& tableQuality = GetFormMap();
	auto iTable = tableQuality.find(order);
	
	return (iTable != tableQuality.end()) ? iTable->second : EPieceForm::FORM_CONE;

}

// Retrieves a string and convert it into a EPieceColor enum.
EPieceColor UEProductProperties::ConverStringToEnumColor(FString color)
{
	std::string order = std::string(TCHAR_TO_UTF8(*color));
	auto& tableQuality = GetColorMap();
	auto iTable = tableQuality.find(order);
	
	return (iTable != tableQuality.end()) ? iTable->second : EPieceColor::COLOR_BLUE;

}
