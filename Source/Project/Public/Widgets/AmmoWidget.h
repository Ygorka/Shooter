// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmmoWidget.generated.h"

class UImage;
class UTextBlock;
class APlayerC;

UCLASS()
class PROJECT_API UAmmoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void ChangeAmmo(int32 NewAmmo);

protected:
	virtual void NativeConstruct() override;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* WeaponImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* AmmoText;

private:

	int32 Clip;

	UPROPERTY()
	APlayerC* Character;

};
