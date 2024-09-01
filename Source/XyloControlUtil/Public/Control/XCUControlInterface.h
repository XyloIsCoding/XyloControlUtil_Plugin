// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "XCUControlInterface.generated.h"

class UXCUControlComponent;
struct FInputActionValue;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UXCUControlInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOCONTROLUTIL_API IXCUControlInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	UXCUControlComponent* GetControlComponent();

	/** Called by Control Component */
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void Input_InputTagTriggered(const FInputActionValue& Value, FGameplayTag InputTag);
	/** Called by Control Component */
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void Input_InputTagStarted(const FInputActionValue& Value, FGameplayTag InputTag);
	/** Called by Control Component */
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void Input_InputTagOngoing(const FInputActionValue& Value, FGameplayTag InputTag);
	/** Called by Control Component */
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void Input_InputTagCompleted(const FInputActionValue& Value, FGameplayTag InputTag);
	/** Called by Control Component */
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void Input_InputTagCanceled(const FInputActionValue& Value, FGameplayTag InputTag);
};
