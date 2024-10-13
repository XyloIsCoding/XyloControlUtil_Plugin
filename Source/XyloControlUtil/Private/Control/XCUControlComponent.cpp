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
	
	if (const UXCUControlComponent* ControlComponent = FindControlComponent(Actor))
	{
		for (const FXCUInputMappingContext& Mapping : ControlComponent->DefaultInputMappings)
		{
			if (const UXCUInputConfig* InputConfig = Mapping.InputConfig.Get())
			{
				if (const UInputAction* IA = InputConfig->FindInputActionForTag(InputTag))
				{
					return IA;
				}
			}
		}
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
	
	
	for (const FXCUInputMappingContext& Mapping : DefaultInputMappings)
	{
		if (UXCUInputConfig* InputConfig = Mapping.InputConfig.Get())
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
			UXCUInputComponent* XCUIC = Cast<UXCUInputComponent>(PlayerInputComponent);
			if (ensureMsgf(XCUIC, TEXT("Unexpected Input Component class! The Gameplay Abilities will not be bound to their inputs. Change the input component to UXCUInputComponent or a subclass of it.")))
			{
				// Add the key mappings that may have been set by the player
				XCUIC->AddInputMappings(InputConfig, Subsystem);

				// This is where we actually bind and input action to a gameplay tag, which means that Gameplay Ability Blueprints will
				// be triggered directly by these input actions Triggered events. 
				TArray<uint32> BindHandles;
				XCUIC->BindActions(InputConfig, this, &ThisClass::OnInputTagTriggered, &ThisClass::OnInputTagStarted, &ThisClass::OnInputTagOngoing, &ThisClass::OnInputTagCompleted, &ThisClass::OnInputTagCanceled, /*out*/ BindHandles);
			}
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
    	XCUIC->BindActions(NewInputConfig, this, &ThisClass::OnInputTagTriggered, &ThisClass::OnInputTagStarted, &ThisClass::OnInputTagOngoing, &ThisClass::OnInputTagCompleted, &ThisClass::OnInputTagCanceled, /*out*/ BindHandles);
    }
}

void UXCUControlComponent::RemoveAdditionalInputConfig(const UXCUInputConfig* RemoveInputConfig)
{
	//@TODO: Implement
}

void UXCUControlComponent::OnInputTagTriggered(const FInputActionValue& Value, FGameplayTag InputTag)
{
	// Interface Call
	if (GetControlInterface())
	{
		ControlInterface->Execute_OnInputTagTriggered(GetOwner(), Value, InputTag);
	}
}

void UXCUControlComponent::OnInputTagStarted(const FInputActionValue& Value, FGameplayTag InputTag)
{
	// Interface Call
	if (GetControlInterface())
	{
		ControlInterface->Execute_OnInputTagStarted(GetOwner(), Value, InputTag);
	}
}

void UXCUControlComponent::OnInputTagOngoing(const FInputActionValue& Value, FGameplayTag InputTag)
{
	// Interface Call
	if (GetControlInterface())
	{
		ControlInterface->Execute_OnInputTagOngoing(GetOwner(), Value, InputTag);
	}
}

void UXCUControlComponent::OnInputTagCompleted(const FInputActionValue& Value, FGameplayTag InputTag)
{
	// Interface Call
	if (GetControlInterface())
	{
		ControlInterface->Execute_OnInputTagCompleted(GetOwner(), Value, InputTag);
	}
}

void UXCUControlComponent::OnInputTagCanceled(const FInputActionValue& Value, FGameplayTag InputTag)
{
	// Interface Call
	if (GetControlInterface())
	{
		ControlInterface->Execute_OnInputTagCanceled(GetOwner(), Value, InputTag);
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/



