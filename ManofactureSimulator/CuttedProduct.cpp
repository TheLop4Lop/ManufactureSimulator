// Fill out your copyright notice in the Description page of Project Settings.


#include "CuttedProduct.h"

// Sets cutted piece product code.
void ACuttedProduct::SetCuttedProductCode(FString& code)
{
    cuttedProductCode = code;

}

// Gets cutted piece product code.
FString& ACuttedProduct::GetCuttedProductCode()
{
    return cuttedProductCode;

}
