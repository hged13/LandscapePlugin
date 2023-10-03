// Copyright Epic Games, Inc. All Rights Reserved.

#include "LandscapePluginGameMode.h"
#include "LandscapePluginCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALandscapePluginGameMode::ALandscapePluginGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
