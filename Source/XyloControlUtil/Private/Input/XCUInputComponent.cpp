// Copyright XyloIsCoding


#include "Input/XCUInputComponent.h"


// Sets default values for this component's properties
UXCUInputComponent::UXCUInputComponent(const FObjectInitializer& ObjectInitializer)
{
}

/*--------------------------------------------------------------------------------------------------------------------*/
/* Input Mappings */

void UXCUInputComponent::AddInputMappings(const UXCUInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);

	// Here you can handle any custom logic to add something from your input config if required
}

void UXCUInputComponent::RemoveInputMappings(const UXCUInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);

	// Here you can handle any custom logic to remove input mappings that you may have added above
}

/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Input Action Binding */

void UXCUInputComponent::RemoveBinds(TArray<uint32>& BindHandles)
{
	for (uint32 Handle : BindHandles)
	{
		RemoveBindingByHandle(Handle);
	}
	BindHandles.Reset();
}

/*--------------------------------------------------------------------------------------------------------------------*/



