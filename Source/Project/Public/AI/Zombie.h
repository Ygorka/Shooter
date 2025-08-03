// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Zombie.generated.h"

class UHealthComponent;
class UWidgetComponent;
class UZombieHealthWidget;

UCLASS()
class PROJECT_API AZombie : public ACharacter
{
	GENERATED_BODY()

public:
	AZombie();

protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY()
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly)
	float DestroyActorTime = 5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UZombieHealthWidget* ZombieHealthWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UWidgetComponent* WidgetComponent;

	void Death();

};
