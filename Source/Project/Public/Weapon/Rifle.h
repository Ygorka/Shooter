// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rifle.generated.h"

class USkeletalMeshComponent;
class UArrowComponent;
class UPointLightComponent;

UCLASS()
class PROJECT_API ARifle : public AActor
{
	GENERATED_BODY()

public:	
	ARifle();

	UArrowComponent* GetArrow() const { return ArrowComponent; }

	void LightShoot();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* ArrowComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPointLightComponent* PointLight;

	FTimerHandle PointTimer;
};
