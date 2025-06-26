// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameModeC.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AMainGameModeC : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Player")
	TSubclassOf<APawn> PlayerPawnClass;

	AMainGameModeC();
	
};
