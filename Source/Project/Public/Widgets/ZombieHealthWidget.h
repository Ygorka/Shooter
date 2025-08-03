// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ZombieHealthWidget.generated.h"

class UProgressBar;

UCLASS()
class PROJECT_API UZombieHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UProgressBar* GetProgressBar() const;
protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;
};
