// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XCUInputBlueprintLibrary.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class XYLOCONTROLUTIL_API UXCUInputBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static bool GetKeyForInputAction(FText& KeyName, const UObject* WorldContextObject, const UInputAction* InputAction);
};
