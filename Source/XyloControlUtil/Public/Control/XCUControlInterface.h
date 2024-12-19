// Copyright XyloIsCoding 2024

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
	UXCUControlComponent* GetControlComponent() const;
	virtual UXCUControlComponent* GetControlComponent_Implementation() const = 0;
	
	/** Called by Control Component */
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void OnInputTagTriggered(const FInputActionValue& Value, FGameplayTag InputTag);
	/** Called by Control Component */
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void OnInputTagStarted(const FInputActionValue& Value, FGameplayTag InputTag);
	/** Called by Control Component */
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void OnInputTagOngoing(const FInputActionValue& Value, FGameplayTag InputTag);
	/** Called by Control Component */
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void OnInputTagCompleted(const FInputActionValue& Value, FGameplayTag InputTag);
	/** Called by Control Component */
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void OnInputTagCanceled(const FInputActionValue& Value, FGameplayTag InputTag);
};
