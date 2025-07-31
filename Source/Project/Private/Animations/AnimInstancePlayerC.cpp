// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/AnimInstancePlayerC.h"
#include "Character/PlayerC.h"

void UAnimInstancePlayerC::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<APlayerC>(TryGetPawnOwner());
}

void UAnimInstancePlayerC::NativeUpdateAnimation(float DeltaTime) {
	Super::NativeUpdateAnimation(DeltaTime);

	if (!IsValid(Character)) return;
	Speed = Character->GetVelocity().Size2D();
	bIsAiming = Character->GetAiming();
	FVector Velocity = Character->GetVelocity();
	FRotator Rotation = Character->GetActorRotation();
	Direction = CalculateDirection(Velocity, Rotation);
	
	if (bIsAiming)
	{
	FRotator DeltaRotation = (Character->GetBaseAimRotation() - Character->GetActorRotation()).GetNormalized();
	AimOffset = FMath::Clamp(DeltaRotation.Pitch * -1.0f, MinPichRotation, MaxPichRotation);
	}
	else
	{
		AimOffset = 0.0f;
	}
}