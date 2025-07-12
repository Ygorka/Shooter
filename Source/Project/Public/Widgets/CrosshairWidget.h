// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairWidget.generated.h"

class UImage;
class APlayerC;
class UWidgetAnimation;

UCLASS()
class PROJECT_API UCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ZoomCrosshair;
private:

	UPROPERTY(meta = (BindWidget))
	UImage* CrosshairImg;

	UPROPERTY()
	APlayerC* Character;

	UFUNCTION()
	void OnAimmingEvent(bool NewIsAiming);
};
