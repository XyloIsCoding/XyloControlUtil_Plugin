// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "XCUControlComponent.generated.h"


class UInputAction;
struct FInputActionValue;
struct FGameplayTag;
class IXCUControlInterface;
class UXCUInputConfig;
class UInputMappingContext;

USTRUCT()
struct FXCUInputMappingContext
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Input", meta=(AssetBundles="Client,Server"))
	TObjectPtr<UInputMappingContext> InputMapping;

	// Higher priority input mappings will be prioritized over mappings with a lower priority.
	UPROPERTY(EditAnywhere, Category="Input")
	int32 Priority = 0;
	
	/** If true, then this mapping context will be registered with the settings when this game feature action is registered. */
	UPROPERTY(EditAnywhere, Category="Input")
	bool bRegisterWithSettings = true;
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class XYLOCONTROLUTIL_API UXCUControlComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UXCUControlComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UPawnComponent Interface
	 */
	
protected:
	virtual void BeginPlay() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * Control
	 */

public:
	/** Returns the Control component if one exists on the specified actor. */
	UFUNCTION(BlueprintPure, Category = "XCU|Control")
	static UXCUControlComponent* FindControlComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UXCUControlComponent>() : nullptr); }

	UFUNCTION(BlueprintPure)
	static const UInputAction* GetInputActionForInputTag(const AActor* Actor, const FGameplayTag InputTag);
	
public:
	IXCUControlInterface* GetControlInterface();
private:
	IXCUControlInterface* ControlInterface;

	/*--------------------------------------------------------------------------------------------------------------------*/
	/* Input */

public:
	/* Mapping Context */
	UPROPERTY(EditAnywhere, Category = "Input")
	TArray<FXCUInputMappingContext> DefaultInputMappings;
	
	// Input configuration used by player controlled pawns to create input mappings and bind input actions.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UXCUInputConfig> InputConfig;
	
public:
	virtual void InitializePlayerInput(UInputComponent* PlayerInputComponent);
	/** Adds mode-specific input config */
	void AddAdditionalInputConfig(const UXCUInputConfig* InputConfig);
	/** Removes a mode-specific input config if it has been added */
	void RemoveAdditionalInputConfig(const UXCUInputConfig* InputConfig);
	
	
	virtual void Input_AbilityInputTagTriggered(const FInputActionValue& Value, FGameplayTag InputTag);
	virtual void Input_AbilityInputTagStarted(const FInputActionValue& Value, FGameplayTag InputTag);
	virtual void Input_AbilityInputTagOngoing(const FInputActionValue& Value, FGameplayTag InputTag);
	virtual void Input_AbilityInputTagCompleted(const FInputActionValue& Value, FGameplayTag InputTag);
	virtual void Input_AbilityInputTagCanceled(const FInputActionValue& Value, FGameplayTag InputTag);
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
	
};
