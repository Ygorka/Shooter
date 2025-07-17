// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Rifle.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"

ARifle::ARifle()
{
    PrimaryActorTick.bCanEverTick = true;

    // 1. Сначала создаем и назначаем корневой компонент
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // 2. Затем создаем и прикрепляем скелетный меш
    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SkeletalMesh->SetupAttachment(RootComponent); // Явно указываем корневой компонент

    // 3. Создаем и прикрепляем компонент стрелки
    ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("MuzzleDirection"));
    ArrowComponent->SetupAttachment(RootComponent);
}


