// Copyright Epic Games, Inc. All Rights Reserved.

#include "proceduralGenerationGameModeBase.h"
#include "proceduralGenerationGameModeBase.h"
#include "Player_Character.h"

AproceduralGenerationGameModeBase::AproceduralGenerationGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Player_Character"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
