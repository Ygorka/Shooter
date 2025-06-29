// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Rifle.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
ARifle::ARifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SkeletalMesh->SetupAttachment(RootComponent);

    // Создаем и настраиваем компонент стрелки
    ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("MuzzleDirection"));
    ArrowComponent->SetupAttachment(RootComponent);
}


