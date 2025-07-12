// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstancePlayerC.generated.h"

class APlayerC;

UCLASS()
class PROJECT_API UAnimInstancePlayerC : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;


protected:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsAiming;

	UPROPERTY(BlueprintReadOnly)
	float AimOffset;

private:
	UPROPERTY(EditDefaultsOnly)
	APlayerC* Character;

	UPROPERTY(EditDefaultsOnly, Category = "AimOffset")
	float MinPichRotation;

	UPROPERTY(EditDefaultsOnly, Category = "AimOffset")
	float MaxPichRotation;
};
