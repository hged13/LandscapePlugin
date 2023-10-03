// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "GenerateLandscapeStyle.h"

class FGenerateLandscapeCommands : public TCommands<FGenerateLandscapeCommands>
{
public:

	FGenerateLandscapeCommands()
		: TCommands<FGenerateLandscapeCommands>(TEXT("GenerateLandscape"), NSLOCTEXT("Contexts", "GenerateLandscape", "GenerateLandscape Plugin"), NAME_None, FGenerateLandscapeStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenHeightmapDialog;
};
