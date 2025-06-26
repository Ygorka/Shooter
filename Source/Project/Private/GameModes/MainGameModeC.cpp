// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/MainGameModeC.h"
#include "Character/PlayerC.h"

AMainGameModeC::AMainGameModeC() {
	//DefaultPawnClass = APlayerC::StaticClass();
	if (PlayerPawnClass) {
		DefaultPawnClass = PlayerPawnClass;
	}
	else {
		DefaultPawnClass = APlayerC::StaticClass();
	}
}