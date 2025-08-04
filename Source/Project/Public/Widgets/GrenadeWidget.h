// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GrenadeWidget.generated.h"

class UImage;
class UTextBlock;
class APlayerC;

UCLASS()
class PROJECT_API UGrenadeWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
private:
	UPROPERTY(meta = (BindWidget))
	UImage* GrenadeImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GrenadeText;

	UFUNCTION()
	void ChangeGrenadeCount(int32 NewGrenade);

	APlayerC* Player;
};
