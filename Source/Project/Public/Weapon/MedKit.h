// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IOnTakeHealth.h"
#include "MedKit.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USoundBase;

UCLASS()
class PROJECT_API AMedKit : public AActor, public IIOnTakeHealth
{
	GENERATED_BODY()
	
public:	
	AMedKit();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Box;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
	USoundBase* FirstAidKitSound;
private:
	UPROPERTY(EditDefaultsOnly)
	float Heal = 25.f;
};
