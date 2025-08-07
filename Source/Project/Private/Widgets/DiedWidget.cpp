// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DiedWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"

void UDiedWidget::NativePreConstruct()
{
	InMainMenuButton->OnClicked.AddDynamic(this, &ThisClass::OnClickMenu);
	RestartButton->OnClicked.AddDynamic(this, &ThisClass::OnClickRestart);

	PlayerController = Cast<APlayerController>(GetOwningPlayer());
}

void UDiedWidget::NativeConstruct()
{
	if (!GetWorld() && !DeathSound) return;

	UGameplayStatics::PlaySound2D(GetWorld(), DeathSound, 0.3f);
	FTimerHandle ShowWidgetTimer;
	GetWorld()->GetTimerManager().SetTimer(ShowWidgetTimer, this, &ThisClass::Death, 0.5f, false);
}

void UDiedWidget::Death()
{

	if (!GetWorld()) return;

	PlayerController->SetShowMouseCursor(true);

	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetWidgetToFocus(TakeWidget());
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeGameAndUI);

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void UDiedWidget::OnClickMenu()
{
	if (!GetWorld() && !PlayerController) return;

	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
}

void UDiedWidget::OnClickRestart()
{
	if (!GetWorld() && !PlayerController) return;

	UGameplayStatics::OpenLevel(GetWorld(), MainLevelName);

	PlayerController->SetShowMouseCursor(false);

	FInputModeGameOnly InputModeGameOnly;
	PlayerController->SetInputMode(InputModeGameOnly);

	UGameplayStatics::SetGamePaused(GetWorld(), false);

}
