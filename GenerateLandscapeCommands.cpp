// Copyright Epic Games, Inc. All Rights Reserved.

#include "GenerateLandscapeCommands.h"

#define LOCTEXT_NAMESPACE "FGenerateLandscapeModule"

void FGenerateLandscapeCommands::RegisterCommands()
{
	UI_COMMAND(OpenHeightmapDialog, "Open Heightmap", "Opens a file dialog to select a heightmap", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
