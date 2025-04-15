// Copyright XyloIsCoding 2024

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XCUControlUtilLibrary.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class XYLOCONTROLUTIL_API UXCUControlUtilLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static bool GetKeyForInputAction(FText& KeyName, const UObject* WorldContextObject, const UInputAction* InputAction);
};
