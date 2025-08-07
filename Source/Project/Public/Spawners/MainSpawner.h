// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainSpawner.generated.h"

class UBoxComponent;

UCLASS()
class PROJECT_API AMainSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AMainSpawner();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UPROPERTY()
	UBoxComponent* Box;

	AActor* Spawner(FVector Location, FVector Scaled);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Class;

private:
	UPROPERTY(EditDefaultsOnly)
	float SpawnRate = 5.f;

	UPROPERTY(EditDefaultsOnly)
	float HeightObject = 50.f;

	UPROPERTY()
	FTimerHandle SpawnTimer;
};
