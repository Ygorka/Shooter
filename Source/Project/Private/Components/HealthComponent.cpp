// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	OnHealthChange.Broadcast(CurrentHealth, MaxHealth);
}


void UHealthComponent::AddHealth(float Amount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0, MaxHealth);

	OnHealthChange.Broadcast(CurrentHealth, MaxHealth);
}

void UHealthComponent::ReduceDamage(float Amount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0, MaxHealth);

	OnHealthChange.Broadcast(CurrentHealth, MaxHealth);
}

float UHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

float UHealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

float UHealthComponent::GetHealthPercent()
{
	return CurrentHealth / MaxHealth;
}