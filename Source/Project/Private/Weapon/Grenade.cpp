// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Grenade.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundAttenuation.h"
#include "Particles/ParticleSystem.h"

AGrenade::AGrenade()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

}

void AGrenade::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle BoomTimer;
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(BoomTimer, this, &ThisClass::GrenadeExplosion, 1.f, false);
	}
}

void AGrenade::GrenadeExplosion()
{
	TArray<AActor*> IgnoredActor;
	IgnoredActor.Add(this);
	IgnoredActor.Add(GetOwner());

	if (!GetWorld() && DamageExplosion && ExplosionSound && SAExplosion && ExplosionPartical) return;
	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageExplosion, GetActorLocation(), RadiusExplosion, nullptr, IgnoredActor, this, GetInstigatorController());

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation(), ExplosionVolume, 1.f, 0.0f, SAExplosion);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionPartical, GetActorLocation(), FRotator::ZeroRotator);

	Destroy();
}

