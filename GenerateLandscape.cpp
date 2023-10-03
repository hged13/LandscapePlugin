// Copyright Epic Games, Inc. All Rights Reserved.

#include "GenerateLandscape.h"
#include "GenerateLandscapeStyle.h"
#include "GenerateLandscapeCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "AssetToolsModule.h"
#include "Misc/FileHelper.h"
#include "UnrealEd.h"

#include "AssetRegistry/AssetRegistryModule.h"





static const FName GenerateLandscapeTabName("GenerateLandscape");

#define LOCTEXT_NAMESPACE "FGenerateLandscapeModule"

void FGenerateLandscapeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FGenerateLandscapeStyle::Initialize();
	FGenerateLandscapeStyle::ReloadTextures();

	FGenerateLandscapeCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FGenerateLandscapeCommands::Get().OpenHeightmapDialog,
		FExecuteAction::CreateRaw(this, &FGenerateLandscapeModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FGenerateLandscapeModule::RegisterMenus));
}

void FGenerateLandscapeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FGenerateLandscapeStyle::Shutdown();

	FGenerateLandscapeCommands::Unregister();
}

void FGenerateLandscapeModule::PluginButtonClicked()
{
	// Import the heightmap
	GenerateLandscapeProxy();
	
	}



void FGenerateLandscapeModule::GenerateLandscapeProxy() {
	UE_LOG(LogTemp, Error, TEXT("BUTTon CLICKED"));

	// 1. Get the editor mode and world.
	FEdMode* LandscapeEdMode = GLevelEditorModeTools().GetActiveMode(FBuiltinEditorModes::EM_Landscape);
	if (LandscapeEdMode) {
		UE_LOG(LogTemp, Error, TEXT("Things are goin"));


	}


	UWorld* World = LandscapeEdMode->GetWorld();
	if (World) {
		UE_LOG(LogTemp, Error, TEXT("We have a world!!"));


	}

	// Create a Zero Vector for the Location
	const FVector LocationZeroVector = FVector::ZeroVector;

	// Create a Zero Rotation for no rotation
	const FRotator RotationZero = FRotator::ZeroRotator;

	// Create a Scale Vector for standard scale
	const FVector ScaleVector = FVector(1.0f, 1.0f, 1.0f);

	// Create a Zero Offset since you want everything at 0,0
	const FVector Offset = FVector::ZeroVector;

	// Create an Identity Transform to construct the Landscape at the origin with no rotation and standard scale.
	const FTransform Transform = FTransform(RotationZero, LocationZeroVector, ScaleVector);

	// Compute the hypothetical QuadsPerComponent assuming you have a specific value in mind or you have computed it before
	const int32 QuadsPerComponent = 63; // Example static value, replace with the actual value you want.

	// Transform the Vector
	const FVector TransformedVector = Transform.TransformVector(FVector(-QuadsPerComponent / 2, -QuadsPerComponent / 2, 0));

	// Now, spawning the Landscape actor at 0,0 Location with 0 Rotation.
	ALandscape* Landscape = World->SpawnActor<ALandscape>(LocationZeroVector + TransformedVector, RotationZero);
	
	UE_LOG(LogTemp, Error, TEXT("SUUUUCCCCESSSSS"));

	FGuid LandscapeGuid = FGuid::NewGuid();

	// Define these based on your landscape requirements
	const int32 NumComponentsX = 1; // Example value
	const int32 NumComponentsY = 1; // Example value
	const int32 NumSectionsPerComponent = 1; // Example value

	// Calculate SizeX and SizeY
	const int32 SizeX = NumComponentsX * NumSectionsPerComponent * QuadsPerComponent + 1;
	const int32 SizeY = NumComponentsY * NumSectionsPerComponent * QuadsPerComponent + 1;

	

	// Other parameters for Import function need to be defined
	Landscape->Import(FGuid::NewGuid(), 0, 0, SizeX - 1, SizeY - 1, /*... other parameters ...*/);
	UE_LOG(LogTemp, Warning, TEXT("Landscape imported successfully!"));


	


	}









void FGenerateLandscapeModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FGenerateLandscapeCommands::Get().OpenHeightmapDialog, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FGenerateLandscapeCommands::Get().OpenHeightmapDialog));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGenerateLandscapeModule, GenerateLandscape)