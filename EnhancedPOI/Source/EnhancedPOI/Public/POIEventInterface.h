// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "POIEventInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UPOIEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ENHANCEDPOI_API IPOIEventInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	void OnPOIShow();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	void OnPOIHide();
};
