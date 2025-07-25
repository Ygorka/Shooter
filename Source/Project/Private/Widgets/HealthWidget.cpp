// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/HealthWidget.h"
#include "Character/PlayerC.h"
#include "Components/HealthComponent.h"
#include "Components/ProgressBar.h"

void UHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PlayerController = Cast<APlayerController>(GetOwningPlayer());
	if (!PlayerController) return;

	APlayerC* Character = Cast<APlayerC>(PlayerController->GetPawn());
	if (!Character) return;

	UHealthComponent* HealthComponent = Character->GetHealthComponent();
	if (!HealthComponent) return;

	HealthComponent->OnHealthChange.AddDynamic(this, &ThisClass::ChangePercent);

	ChangePercent(HealthComponent->GetCurrentHealth(), HealthComponent->GetMaxHealth());
}

void UHealthWidget::ChangePercent(float CurrentHealth, float MaxHealth)
{
	float Percent = CurrentHealth / MaxHealth;

	HealthProgressBar->SetPercent(Percent);
}