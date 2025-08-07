// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ZombieAIC.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "TimerManager.h"
#include "AITypes.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"

AZombieAIC::AZombieAIC()
{
}

void AZombieAIC::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld()) return;
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	ZombieCharacter = Cast<ACharacter>(GetPawn());

	if (!Player && !ZombieCharacter) return;

	Mesh = ZombieCharacter->GetMesh();
	if (Mesh)
	{
		Mesh->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::OnAttackEnded);
		Mesh->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &ThisClass::OnNotifyBegin);
	}
	else
	{
		return;
	}

	if (GetPathFollowingComponent())
	{
		GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &ThisClass::OnMoveCompleted);
	}
	else
	{
		return;
	}

	MoveToCharacter();
}

void AZombieAIC::MoveToCharacter()
{
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Player);
	MoveRequest.SetAcceptanceRadius(AcceprionRadius);

	FPathFollowingRequestResult MoveResutl = MoveTo(MoveRequest);
	CurrentMoveRequestID = MoveResutl.MoveId;

	GetWorld()->GetTimerManager().SetTimer(ChaseTimer, this, &ThisClass::MoveToCharacter, 0.01f, true);
}

void AZombieAIC::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (RequestID == CurrentMoveRequestID)
	{
		if (Result.Code == EPathFollowingResult::Success)
		{
			GetWorld()->GetTimerManager().ClearTimer(ChaseTimer);
			Attack();
		}
	}
}

void AZombieAIC::Attack()
{
	float DistanceDifference = FVector::Distance(Player->GetActorLocation(), ZombieCharacter->GetActorLocation());
	if (DistanceDifference <= Distance)
	{
		if (AttackAnimation)
		{
		Mesh->GetAnimInstance()->Montage_Play(AttackAnimation,1.0f);
		}
	}
	else
	{
		MoveToCharacter();
	}
}

void AZombieAIC::OnAttackEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == AttackAnimation && !bInterrupted)
	{
		Attack();
	}
}

void AZombieAIC::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (!GetWorld()) return;
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	Mesh->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &ThisClass::OnAttackEnded);

	GetPathFollowingComponent()->OnRequestFinished.RemoveAll(this);
}

void AZombieAIC::OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{

	if (NotifyName == "HitStart")
	{
		IIOnZombieAttack::Execute_IStartAttack(GetPawn());
	}
	else {
		IIOnZombieAttack::Execute_IStopAttack(GetPawn());
	}
}