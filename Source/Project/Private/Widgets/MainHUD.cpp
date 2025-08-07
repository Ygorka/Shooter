// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainHUD.h"
#include "Widgets/MainWidget.h"
#include "Widgets/CrosshairWidget.h"
#include "Widgets/DiedWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainWidgetClass)
	{
		MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetClass);
		if (MainWidget)
		{
			MainWidget->AddToViewport();
		}
	}

	if (CrosshairWidgetClass)
	{
		CrosshairWidget = CreateWidget<UCrosshairWidget>(GetWorld(), CrosshairWidgetClass);
		if (CrosshairWidget)
		{
			CrosshairWidget->AddToViewport();
		}
	}

}

void AMainHUD::Death_Implementation()
{
	if (GetWorld() && DiedWidgetClass)
	{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	DiedWidget = CreateWidget<UDiedWidget>(GetWorld(), DiedWidgetClass);
	if (DiedWidget)
	{
		DiedWidget->AddToViewport();
	}
	}
}