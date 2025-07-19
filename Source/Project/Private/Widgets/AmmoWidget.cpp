// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/AmmoWidget.h"
#include "Components/TextBlock.h"
#include "Character/PlayerC.h"

void UAmmoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (APlayerController* PlayerController = Cast<APlayerController>(GetOwningPlayer()))
	{
		Character = Cast<APlayerC>(PlayerController->GetPawn());
		if (Character)
		{
			Character->OnChangeAmmo.AddDynamic(this, &ThisClass::ChangeAmmo);
			Clip = Character->GetMaxAmmo();
		}
	}
}

void UAmmoWidget::ChangeAmmo(int32 NewAmmo)
{
	FText AmmoAndClip = FText::Format(
		FText::FromString("{0} / {1}"),
		FText::AsNumber(NewAmmo),
		FText::AsNumber(Clip)
	);

	AmmoText->SetText(AmmoAndClip);
}