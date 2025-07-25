// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponClip.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SpotLightComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PlayerC.h"

AWeaponClip::AWeaponClip()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(RootComponent);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(RootComponent);
}

void AWeaponClip::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		Character = Cast<APlayerC>(PlayerController->GetPawn());
		if (!Character) return;
	}

	Box->OnComponentBeginOverlap.AddDynamic(this, &AWeaponClip::OnBeginOverlap);
}

void AWeaponClip::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Character == Cast<APlayerC>(OtherActor))
	{
		AddAmmo();
	}
}

void AWeaponClip::AddAmmo()
{
	if (Character->GetAmmo() < Character->GetMaxAmmo())
	{
		Character->SetAmmo(FMath::Clamp(Character->GetAmmo() + Character->GetMaxAmmo(), 0, Character->GetMaxAmmo()));
		Character->OnChangeAmmo.Broadcast(Character->GetAmmo());
		if (AmmoTakeSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), AmmoTakeSound, 1.0f);
		}
		Destroy();
	}
}

