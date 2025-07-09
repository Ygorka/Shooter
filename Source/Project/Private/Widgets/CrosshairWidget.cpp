// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CrosshairWidget.h"
#include "Components/Image.h"
#include "Character/PlayerC.h"

void UCrosshairWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (APlayerController* PlayerController = Cast<APlayerController>(GetOwningPlayer()))
	{
		Character = Cast<APlayerC>(PlayerController->GetPawn());
		if (Character)
		{
			Character->OnAiming.AddDynamic(this, &ThisClass::OnAimmingEvent);
		}
	}
	
}

void UCrosshairWidget::NativeDestruct()
{
	if (Character)
	{
		Character->OnAiming.RemoveDynamic(this, &ThisClass::OnAimmingEvent);
	}

	Super::NativeDestruct();
}

void UCrosshairWidget::OnAimmingEvent(bool NewIsAiming)
{
	if (NewIsAiming)
	{
		CrosshairImg->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		CrosshairImg->SetVisibility(ESlateVisibility::Hidden);
	}
}
