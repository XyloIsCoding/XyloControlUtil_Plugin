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

USTRUCT(BlueprintType)
struct FXCUInputMappingContext
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Input", meta=(AssetBundles="Client,Server"))
	TObjectPtr<UInputMappingContext> InputMapping;

	// Input configuration used by player controlled pawns to create input mappings and bind input actions.
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UXCUInputConfig> InputConfig;
	
	// Higher priority input mappings will be prioritized over mappings with a lower priority.
	UPROPERTY(EditAnywhere, Category="Input")
	int32 Priority = 0;
	
	/** If true, then this mapping context will be registered with the settings when this game feature action is registered. */
	UPROPERTY(EditAnywhere, Category="Input")
	bool bRegisterWithSettings = true;
};


/*
 * Add this component to a character together with the control interface.
 * Call InitializePlayerInput to activate the component.
 */
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

	UFUNCTION(BlueprintPure, Category = "Input")
	static const UInputAction* GetInputActionForInputTag(const AActor* Actor, const FGameplayTag InputTag);
	
public:
	IXCUControlInterface* GetControlInterface();
private:
	IXCUControlInterface* ControlInterface;

/*--------------------------------------------------------------------------------------------------------------------*/
	/* Input */

public:
	/** Mapping Context */
	UPROPERTY(EditAnywhere, Category = "Input")
	TArray<FXCUInputMappingContext> DefaultInputMappings;

public:
	/** Call to initialize component */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void InitializePlayerInput(UInputComponent* PlayerInputComponent);
	
	/** Adds mode-specific input config */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void AddAdditionalInputConfig(const UXCUInputConfig* InputConfig); // TODO: make it take a FXCUInputMappingContext, so it adds/removes both input mapping and input config
	/** Removes a mode-specific input config if it has been added */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void RemoveAdditionalInputConfig(const UXCUInputConfig* InputConfig);
	
protected:
	virtual void OnInputTagTriggered(const FInputActionValue& Value, FGameplayTag InputTag);
	virtual void OnInputTagStarted(const FInputActionValue& Value, FGameplayTag InputTag);
	virtual void OnInputTagOngoing(const FInputActionValue& Value, FGameplayTag InputTag);
	virtual void OnInputTagCompleted(const FInputActionValue& Value, FGameplayTag InputTag);
	virtual void OnInputTagCanceled(const FInputActionValue& Value, FGameplayTag InputTag);
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
	
};
