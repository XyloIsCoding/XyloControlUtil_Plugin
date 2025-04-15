// Copyright XyloIsCoding 2024


#include "Input/XCUControlUtilLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

bool UXCUControlUtilLibrary::GetKeyForInputAction(FText& KeyName, const UObject* WorldContextObject, const UInputAction* InputAction)
{
	if (!InputAction || !WorldContextObject) return false;
	
	if (const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0)) //TODO: change for local multiplayer
	{
		if (const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (const UEnhancedInputLocalPlayerSubsystem* EnhancedInput = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				TArray<FKey> Keys = EnhancedInput->QueryKeysMappedToAction(InputAction); //TODO: System to find right key to display
				for (FKey Key : Keys)
				{
					KeyName = Key.GetDisplayName();
					return true; 
				}
			}
		}
	}
	return false;
}
