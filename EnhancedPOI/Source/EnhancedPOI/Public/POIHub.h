// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "POIHub.generated.h"

	

/**
 *  get all poi system actors
 */
USTRUCT(BlueprintType)
struct FPOIObjectsPool
{
	GENERATED_BODY()

public:

	FPOIObjectsPool();
	~FPOIObjectsPool();
	
	UPROPERTY(BlueprintReadOnly)
	FName UID;
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> strTags;
	UPROPERTY(BlueprintReadOnly)
	FTransform Transform;
	UPROPERTY(BlueprintReadOnly)
	int StyleIndex = 999;
	UPROPERTY(BlueprintReadOnly)
	UClass* POIActorClass;

	

	
	FString ToJSONString() const
	{
		
		return FString::Printf(TEXT(
			"{ \"UID\": \"%s\", \"Tags\": [\"%s\"], \"Transform\": \"%s\", \"StyleIndex\": %d, \"POIActorClass\": \"%s\" }"),
			*UID.ToString(),*FString::Join(strTags, TEXT("\",\"")), *Transform.ToString(), StyleIndex, *POIActorClass->GetName());
	}

	UPROPERTY()
	bool bIsVisible = false;

	UPROPERTY()
	TMap<FName,AActor*> POICacheMap;



};

UCLASS(Blueprintable)
class ENHANCEDPOI_API UPOIHub : public UObject
{
	GENERATED_BODY()

public:
	UPOIHub();

	UFUNCTION()
	static void GetPOIFast(FName UID);
	
	void RegisterPOI(FName UID, AActor* POIActor)
	{
		POIObjectsPool.POICacheMap.Add(UID, POIActor);
	};

private:
	UPROPERTY()
	FPOIObjectsPool POIObjectsPool;	
};
