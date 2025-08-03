// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieAIC.generated.h"

class ACharacter;
class APawn;
class UAnimMontage;
class USkeletalMeshComponent;

UCLASS()
class PROJECT_API AZombieAIC : public AAIController
{
	GENERATED_BODY()
public:
	AZombieAIC();
protected:
	virtual void BeginPlay() override;

	void MoveToCharacter();
private:
	FTimerHandle ChaseTimer;

	APawn* Player;

	ACharacter* ZombieCharacter;

	UPROPERTY()
	USkeletalMeshComponent* Mesh;

	FAIRequestID CurrentMoveRequestID;

	void Attack();

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);

	UFUNCTION()
	void OnAttackEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(EditDefaultsOnly)
	float Distance = 100.f;

	UPROPERTY(EditDefaultsOnly)
	float AcceprionRadius = 20.f;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AttackAnimation;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
