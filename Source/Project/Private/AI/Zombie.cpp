// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Zombie.h"
#include "Components/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "Components/SphereComponent.h"
#include "Widgets/ZombieHealthWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"

AZombie::AZombie()
{
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetupAttachment(RootComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ShereComponent"));
	SphereComponent->SetupAttachment(GetMesh(), "RightHand");
	SphereComponent->SetSphereRadius(80.f);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

void AZombie::IStartAttack_Implementation()
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IStartAttack_Implementation"));
	if (!GetWorld() && !SphereComponent) return;

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	TArray<AActor*> Zombies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BPZombieClass, Zombies);

	TArray<AActor*> OverlapedActor;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	ObjectType.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	bool Hit = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), SphereComponent->GetComponentLocation(), SphereComponent->GetScaledSphereRadius(), ObjectType, nullptr, Zombies, OverlapedActor);

	if (Hit)
	{
		for (AActor* Actor : OverlapedActor)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("InHit"));
			UGameplayStatics::ApplyDamage(Actor, Damage, GetInstigatorController(), this, nullptr);
		}
	}

}

void AZombie::IStopAttack_Implementation()
{
	if (!GetWorld()) return;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IStopAttack_Implementation"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


