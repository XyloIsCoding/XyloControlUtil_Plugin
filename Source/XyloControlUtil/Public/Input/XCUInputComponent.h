// Copyright XyloIsCoding

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "XCUInputConfig.h"
#include "XCUInputComponent.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
/**
 * Has to be set as the "Default input component class" for the project
 */
UCLASS(Config = Input)
class XYLOCONTROLUTIL_API UXCUInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UXCUInputComponent(const FObjectInitializer& ObjectInitializer);

/*--------------------------------------------------------------------------------------------------------------------*/
	/* Input Mappings */
	
	void AddInputMappings(const UXCUInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const;
	void RemoveInputMappings(const UXCUInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const;

/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
	/* Input Action Binding */
	
	template<class UserClass, typename TriggeredFuncType, typename StartedFuncType, typename OngoingFuncType, typename CompletedFuncType, typename CanceledFuncType>
	void BindActions(const UXCUInputConfig* InputConfig, UserClass* Object, TriggeredFuncType TriggeredFunc, StartedFuncType StartedFunc, OngoingFuncType OngoingFunc, CompletedFuncType CompletedFunc, CanceledFuncType CanceledFunc, TArray<uint32>& BindHandles);

	void RemoveBinds(TArray<uint32>& BindHandles);

/*--------------------------------------------------------------------------------------------------------------------*/
	
};



template <class UserClass, typename TriggeredFuncType, typename StartedFuncType, typename OngoingFuncType, typename CompletedFuncType, typename CanceledFuncType>
void UXCUInputComponent::BindActions(const UXCUInputConfig* InputConfig, UserClass* Object, TriggeredFuncType TriggeredFunc, StartedFuncType StartedFunc, OngoingFuncType OngoingFunc, CompletedFuncType CompletedFunc, CanceledFuncType CanceledFunc, TArray<uint32>& BindHandles)
{
	check(InputConfig);

	for (const FXCUInputAction& Action : InputConfig->InputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (TriggeredFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, TriggeredFunc, Action.InputTag).GetHandle());
			}

			if (StartedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Started, Object, StartedFunc, Action.InputTag).GetHandle());
			}

			if (OngoingFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Ongoing, Object, OngoingFunc, Action.InputTag).GetHandle());
			}

			if (CompletedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Completed, Object, CompletedFunc, Action.InputTag).GetHandle());
			}

			if (CanceledFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Canceled, Object, CanceledFunc, Action.InputTag).GetHandle());
			}
			
		}
	}
}

