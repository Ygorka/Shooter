// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/MedKit.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMedKit::AMedKit()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(RootComponent);

	Box->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AMedKit::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMedKit::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->ImplementsInterface(UIOnTakeHealth::StaticClass()))
	{
		float CurrentHealth;
		float MaxHealth;
		IIOnTakeHealth::Execute_GetCurrentAndMaxHealth(OtherActor, CurrentHealth, MaxHealth);
		if (CurrentHealth < MaxHealth)
		{
			IIOnTakeHealth::Execute_OnTakeHeal(OtherActor, Heal);
			if (FirstAidKitSound)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), FirstAidKitSound, 1.f);
			}
			Destroy();
		}
	}
}

