// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ZombieAnimInstance.h"
#include "AI/Zombie.h"

void UZombieAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Zombie = Cast<AZombie>(TryGetPawnOwner());
}

void UZombieAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (!IsValid(Zombie)) return;
	Speed = Zombie->GetVelocity().Size2D();
}