// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/AnimInstancePlayerC.h"

void UAnimInstancePlayerC::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = TryGetPawnOwner();
}

void UAnimInstancePlayerC::NativeUpdateAnimation(float DeltaTime) {
	Super::NativeUpdateAnimation(DeltaTime);

	if (!IsValid(Character)) return;
	Speed = Character->GetVelocity().Size2D();
	
}