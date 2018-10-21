// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
 

/**
 * 
 */
class BATTLE_TANK_API CheckForValidPointer
{
public:
	CheckForValidPointer();
	~CheckForValidPointer();

	template <typename PointerClass>
	bool CheckPointer(PointerClass* Pointer);

};
