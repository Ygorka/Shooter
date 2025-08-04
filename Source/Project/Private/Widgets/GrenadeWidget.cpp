// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GrenadeWidget.h"
#include "Character/PlayerC.h"
#include "Components/TextBlock.h"

void UGrenadeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetOwningPlayer()))
	{
		Player = Cast<APlayerC>(PlayerController->GetPawn());
		if (Player)
		{
			Player->OnChangeGrenade.AddDynamic(this, &ThisClass::ChangeGrenadeCount);
		}
	}

}

void UGrenadeWidget::ChangeGrenadeCount(int32 NewGrenade)
{
	if (GrenadeText)
	{
		FText GrenadeCountText = FText::AsNumber(NewGrenade);
		GrenadeText->SetText(GrenadeCountText);
	}
}