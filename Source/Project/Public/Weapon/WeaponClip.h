// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponClip.generated.h"

class UStaticMeshComponent;
class USpotLightComponent;
class UBoxComponent;
class APlayerC;
class USoundBase;

UCLASS()
class PROJECT_API AWeaponClip : public AActor
{
	GENERATED_BODY()

	
public:	
	AWeaponClip();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	USpotLightComponent* SpotLight;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Box;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* AmmoTakeSound;
private:

	UPROPERTY()
	APlayerC* Character;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void AddAmmo();
};
