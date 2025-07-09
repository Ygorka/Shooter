// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainHUD.h"
#include "Widgets/MainWidget.h"

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
}