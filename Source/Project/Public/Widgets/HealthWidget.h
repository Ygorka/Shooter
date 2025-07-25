// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

class UProgressBar;
class  UImage;


UCLASS()
class PROJECT_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget) )
	UProgressBar* HealthProgressBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* HealthImage;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void ChangePercent(float CurrentHealth, float MaxHealth);
};
