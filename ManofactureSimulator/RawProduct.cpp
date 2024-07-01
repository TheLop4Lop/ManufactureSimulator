// Fill out your copyright notice in the Description page of Project Settings.


#include "RawProduct.h"

// Sets product code based on initial BaseStorage struct.
void ARawProduct::SetProductCode(FString productCode)
{
	rawProductCode = productCode;

}

// Gets the Product code, this will be readed by the respective machines.
FString ARawProduct::GetRawProductCode()
{
    return rawProductCode;

}
