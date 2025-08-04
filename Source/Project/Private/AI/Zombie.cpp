// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Zombie.h"
#include "Components/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "Widgets/ZombieHealthWidget.h"
#include "TimerManager.h"

AZombie::AZombie()
{
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetupAttachment(RootComponent);
}

void AZombie::BeginPlay()
{
	Super::BeginPlay();

	ZombieHealthWidget = Cast<UZombieHealthWidget>(WidgetComponent->GetUserWidgetObject());
}

float AZombie::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	HealthComponent->ReduceDamage(ActualDamage);

	ZombieHealthWidget->GetProgressBar()->SetPercent(HealthComponent->GetHealthPercent());

	if (HealthComponent->GetCurrentHealth() <= 0.f)
	{
		ZombieHealthWidget->SetVisibility(ESlateVisibility::Hidden);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetMesh()->SetSimulatePhysics(true);

		FTimerHandle DeathTimer;
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &ThisClass::Death, DestroyActorTime, false);
		}
		
	}

	return ActualDamage;
}

void AZombie::Death()
{
	Destroy();
}


