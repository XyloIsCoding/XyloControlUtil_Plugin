// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XCUControlInterface.generated.h"

class UXCUControlComponent;
struct FGameplayTag;
struct FInputActionValue;
// This class does not need to be modified.
UINTERFACE()
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
	virtual UXCUControlComponent* GetControlComponent() = 0;
	
	virtual void Input_AbilityInputTagTriggered(const FInputActionValue& Value, FGameplayTag InputTag);
	virtual void Input_AbilityInputTagStarted(const FInputActionValue& Value, FGameplayTag InputTag);
	virtual void Input_AbilityInputTagOngoing(const FInputActionValue& Value, FGameplayTag InputTag);
	virtual void Input_AbilityInputTagCompleted(const FInputActionValue& Value, FGameplayTag InputTag);
	virtual void Input_AbilityInputTagCanceled(const FInputActionValue& Value, FGameplayTag InputTag);
	
};
