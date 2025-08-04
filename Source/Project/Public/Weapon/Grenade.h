// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grenade.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class USoundBase;
class USoundAttenuation;
class UParticleSystem;

UCLASS()
class PROJECT_API AGrenade : public AActor
{
	GENERATED_BODY()
	
public:	

	AGrenade();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovement;

	void GrenadeExplosion();

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float RadiusExplosion = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageExplosion = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ExplosionSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	float ExplosionVolume = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundAttenuation* SAExplosion;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ExplosionPartical;
};
