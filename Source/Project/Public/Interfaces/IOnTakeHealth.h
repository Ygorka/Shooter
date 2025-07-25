// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IOnTakeHealth.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UIOnTakeHealth : public UInterface
{
	GENERATED_BODY()
};


class PROJECT_API IIOnTakeHealth
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnTakeHeal(float Amount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GetCurrentAndMaxHealth(float& CurrentHealth, float& MaxHealth);
};
