// Copyright XyloIsCoding


#include "Input/XCUInputConfig.h"

UXCUInputConfig::UXCUInputConfig(const FObjectInitializer& ObjectInitializer)
{
}

const UInputAction* UXCUInputConfig::FindInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FXCUInputAction& Action : InputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
