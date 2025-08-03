// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChange, float, CurrentHealth, float, MaxHealth);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCurrentHealth();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable)
	void AddHealth(float Amount);

	UFUNCTION(BlueprintCallable)
	void ReduceDamage(float Amount);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHealthPercent();

	UPROPERTY(BlueprintAssignable)
	FOnHealthChange OnHealthChange;


protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float CurrentHealth;
};
