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
	Speed = TryGetPawnOwner()->GetVelocity().Size2D();
	bIsAiming = Character->GetAiming();
}