// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "LandscapeProxy.h"
#include "Engine/World.h"
#include "Landscape.h"
#include "EditorModes.h"
#include "Engine/Engine.h" // For GEngine
#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Input/Reply.h"
#include "Widgets/SWidget.h"
#include "IDetailCustomization.h"
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"


class FToolBarBuilder;
class FMenuBuilder;

class FGenerateLandscapeModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	void GenerateLandscapeProxy();
	
private:

	void RegisterMenus();


private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
