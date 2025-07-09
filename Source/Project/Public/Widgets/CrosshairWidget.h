// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairWidget.generated.h"

class UImage;
class APlayerC;

UCLASS()
class PROJECT_API UCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	UImage* CrosshairImg;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnAimmingEvent(bool NewIsAiming);
private:
	UPROPERTY()
	APlayerC* Character;
};
