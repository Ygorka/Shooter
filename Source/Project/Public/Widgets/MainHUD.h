// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Interfaces/IDeath.h"
#include "MainHUD.generated.h"

class UMainWidget;
class UCrosshairWidget;
class UDiedWidget;

UCLASS()
class PROJECT_API AMainHUD : public AHUD, public IIDeath
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCrosshairWidget* CrosshairWidget;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainWidget> MainWidgetClass;

	UPROPERTY()
	UMainWidget* MainWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCrosshairWidget> CrosshairWidgetClass;

	UPROPERTY()
	UDiedWidget* DiedWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDiedWidget> DiedWidgetClass;

	virtual void Death_Implementation() override;
};
