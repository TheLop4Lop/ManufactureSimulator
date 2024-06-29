// Fill out your copyright notice in the Description page of Project Settings.


#include "MolderedProduct.h"

// Sets cutted piece product code.
void AMolderedProduct::SetMolderedProductCode(FProductForm code)
{
    molderedProductCode = code;

}

// Gets cutted piece product code.
FProductForm AMolderedProduct::GetMolderedProductCode()
{
    return molderedProductCode;

}
