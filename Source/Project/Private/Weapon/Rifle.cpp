// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Rifle.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/ArrowComponent.h"

ARifle::ARifle()
{
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SkeletalMesh->SetupAttachment(RootComponent);

    ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("MuzzleDirection"));
    ArrowComponent->SetupAttachment(RootComponent);

    PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
    PointLight->SetupAttachment(RootComponent);
}

void ARifle::LightShoot()
{
    PointLight->SetHiddenInGame(false);
    GetWorld()->GetTimerManager().SetTimer(
        PointTimer,
        [this] {
            PointLight->SetHiddenInGame(true);
        },
        0.1f, false
    );
}


