// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckForValidPointer.h"

CheckForValidPointer::CheckForValidPointer()
{
}

CheckForValidPointer::~CheckForValidPointer()
{
}

template<typename PointerClass>
bool CheckForValidPointer::CheckPointer(PointerClass* Pointer)
{
	if (Pointer == nullptr) return false;
	else return true;
}
