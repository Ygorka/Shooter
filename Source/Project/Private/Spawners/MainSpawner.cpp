// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/MainSpawner.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"

// Sets default values
AMainSpawner::AMainSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(RootComponent);

}

void AMainSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (!Box && !Class && GetWorld()) return;
	FVector BoxCenter = Box->GetComponentLocation();
	FVector BoxScaled = Box->GetScaledBoxExtent();

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, [this, BoxCenter, BoxScaled]() {Spawner(BoxCenter, BoxScaled);}, SpawnRate, true);
	}
}

AActor* AMainSpawner::Spawner(FVector Center, FVector Scaled)
{
	if (!GetWorld()) return nullptr;

	FVector RandomPoint = FMath::RandPointInBox(FBox(Center - Scaled, Center + Scaled));

	//Raycast down to find ground 
	FHitResult SpawnHit;
	FVector Start = RandomPoint + FVector(0, 0, 500);
	FVector End = RandomPoint - FVector(0, 0, 1000);

	if (GetWorld()->LineTraceSingleByChannel(SpawnHit, Start, End, ECC_Visibility))
	{
		RandomPoint = SpawnHit.ImpactPoint + FVector(0, 0, HeightObject);
	}
	else
	{
		RandomPoint.Z = Center.Z - Scaled.Z;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(Class, RandomPoint,FRotator::ZeroRotator, SpawnParams);

	return SpawnedActor;
}

void AMainSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (!GetWorld()) return;

	GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
}


