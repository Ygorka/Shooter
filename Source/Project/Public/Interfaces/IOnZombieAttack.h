// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IOnZombieAttack.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UIOnZombieAttack : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_API IIOnZombieAttack
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IStartAttack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IStopAttack();
};
