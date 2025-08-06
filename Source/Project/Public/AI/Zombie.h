// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IOnZombieAttack.h"
#include "Zombie.generated.h"

class UHealthComponent;
class UWidgetComponent;
class UZombieHealthWidget;
class USphereComponent;
class AActor;

UCLASS()
class PROJECT_API AZombie : public ACharacter, public IIOnZombieAttack
{
	GENERATED_BODY()

public:
	AZombie();

protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void IStartAttack_Implementation() override;

	virtual void IStopAttack_Implementation() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UZombieHealthWidget* ZombieHealthWidget;
private:

	UPROPERTY()
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly)
	float DestroyActorTime = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereComponent;

	UPROPERTY(EDitDefaultsOnly)
	TSubclassOf<AActor> BPZombieClass;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 20.f;

	void Death();

};
