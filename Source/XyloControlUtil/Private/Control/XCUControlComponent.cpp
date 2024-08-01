// Fill out your copyright notice in the Description page of Project Settings.


#include "Control/XCUControlComponent.h"

#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "Control/XCUControlInterface.h"

#include "Input/XCUInputComponent.h"
#include "UserSettings/EnhancedInputUserSettings.h"


UXCUControlComponent::UXCUControlComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UPawnComponent Interface
 */

void UXCUControlComponent::BeginPlay()
{
	Super::BeginPlay();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Control
 */

const UInputAction* UXCUControlComponent::GetInputActionForInputTag(const AActor* Actor, const FGameplayTag InputTag)
{
	if (!Actor) return nullptr;
	
	const UXCUControlComponent* ControlComponent = FindControlComponent(Actor);
	if (ControlComponent && ControlComponent->InputConfig)
	{
		return ControlComponent->InputConfig->FindInputActionForTag(InputTag);
	}
	return nullptr;
}

IXCUControlInterface* UXCUControlComponent::GetControlInterface()
{
	if (!ControlInterface)
	{
		ControlInterface = GetOwner<IXCUControlInterface>();
	}
	return ControlInterface;
}

/*--------------------------------------------------------------------------------------------------------------------*/
/* Input */

void UXCUControlComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	const APlayerController* PC = GetController<APlayerController>();
	check(PC);

	const ULocalPlayer* LP = Cast<ULocalPlayer>(PC->GetLocalPlayer());
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	// Remove all config to the local player	
	Subsystem->ClearAllMappings();
	
	
	if (InputConfig)
	{
		for (const FXCUInputMappingContext& Mapping : DefaultInputMappings)
		{
			if (UInputMappingContext* IMC = Mapping.InputMapping.Get())
			{
				if (Mapping.bRegisterWithSettings)
				{
					if (UEnhancedInputUserSettings* Settings = Subsystem->GetUserSettings())
					{
						Settings->RegisterInputMappingContext(IMC);
					}
					
					FModifyContextOptions Options = {};
					Options.bIgnoreAllPressedKeysUntilRelease = false;
					// Actually add the config to the local player							
					Subsystem->AddMappingContext(IMC, Mapping.Priority, Options);
				}
			}
		}

		UXCUInputComponent* XCUIC = Cast<UXCUInputComponent>(PlayerInputComponent);
		if (ensureMsgf(XCUIC, TEXT("Unexpected Input Component class! The Gameplay Abilities will not be bound to their inputs. Change the input component to UXCUInputComponent or a subclass of it.")))
		{
			// Add the key mappings that may have been set by the player
			XCUIC->AddInputMappings(InputConfig, Subsystem);

			// This is where we actually bind and input action to a gameplay tag, which means that Gameplay Ability Blueprints will
			// be triggered directly by these input actions Triggered events. 
			TArray<uint32> BindHandles;
			XCUIC->BindActions(InputConfig, this, &ThisClass::Input_AbilityInputTagTriggered, &ThisClass::Input_AbilityInputTagStarted, &ThisClass::Input_AbilityInputTagOngoing, &ThisClass::Input_AbilityInputTagCompleted, &ThisClass::Input_AbilityInputTagCanceled, /*out*/ BindHandles);
		}
	}
}

void UXCUControlComponent::AddAdditionalInputConfig(const UXCUInputConfig* NewInputConfig)
{
	TArray<uint32> BindHandles;
    
    const APawn* Pawn = GetPawn<APawn>();
    if (!Pawn)
    {
    	return;
    }
    
    const APlayerController* PC = GetController<APlayerController>();
    check(PC);

    const ULocalPlayer* LP = PC->GetLocalPlayer();
    check(LP);

    UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    check(Subsystem);

    UXCUInputComponent* XCUIC = Pawn->FindComponentByClass<UXCUInputComponent>();
    if (ensureMsgf(XCUIC, TEXT("Unexpected Input Component class! The Gameplay Abilities will not be bound to their inputs. Change the input component to UXCUICInputComponent or a subclass of it.")))
    {
    	XCUIC->BindActions(NewInputConfig, this, &ThisClass::Input_AbilityInputTagTriggered, &ThisClass::Input_AbilityInputTagStarted, &ThisClass::Input_AbilityInputTagOngoing, &ThisClass::Input_AbilityInputTagCompleted, &ThisClass::Input_AbilityInputTagCanceled, /*out*/ BindHandles);
    }
}

void UXCUControlComponent::RemoveAdditionalInputConfig(const UXCUInputConfig* RemoveInputConfig)
{
	//@TODO: Implement
}

void UXCUControlComponent::Input_AbilityInputTagTriggered(const FInputActionValue& Value, FGameplayTag InputTag)
{
	// Interface Call
	if (GetControlInterface())
	{
		ControlInterface->Input_AbilityInputTagTriggered(Value, InputTag);
	}
}

void UXCUControlComponent::Input_AbilityInputTagStarted(const FInputActionValue& Value, FGameplayTag InputTag)
{
	// Interface Call
	if (GetControlInterface())
	{
		ControlInterface->Input_AbilityInputTagStarted(Value, InputTag);
	}
}

void UXCUControlComponent::Input_AbilityInputTagOngoing(const FInputActionValue& Value, FGameplayTag InputTag)
{
	// Interface Call
	if (GetControlInterface())
	{
		ControlInterface->Input_AbilityInputTagOngoing(Value, InputTag);
	}
}

void UXCUControlComponent::Input_AbilityInputTagCompleted(const FInputActionValue& Value, FGameplayTag InputTag)
{
	// Interface Call
	if (GetControlInterface())
	{
		ControlInterface->Input_AbilityInputTagCompleted(Value, InputTag);
	}
}

void UXCUControlComponent::Input_AbilityInputTagCanceled(const FInputActionValue& Value, FGameplayTag InputTag)
{
	// Interface Call
	if (GetControlInterface())
	{
		ControlInterface->Input_AbilityInputTagCanceled(Value, InputTag);
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/



