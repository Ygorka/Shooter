// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DiedWidget.generated.h"

class UButton;
class USoundBase;
class APlayerController;

UCLASS()
class PROJECT_API UDiedWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* InMainMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

	void Death();

	UFUNCTION()
	void OnClickMenu();

	UFUNCTION()
	void OnClickRestart();

	UPROPERTY(EditDefaultsOnly)
	USoundBase* DeathSound;

	UPROPERTY(EditDefaultsOnly)
	FName MainLevelName = "MainLevel";

	UPROPERTY()
	APlayerController* PlayerController;
};
