// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "POIHub.generated.h"

	

/**
 *  get all poi system actors
 */
USTRUCT(BlueprintType)
struct FPOIObjectsInfo
{
	GENERATED_BODY()

public:
	FPOIObjectsInfo() = default;
	FPOIObjectsInfo(TSoftObjectPtr<AActor> POI);
	~FPOIObjectsInfo();
	
	
	int32 UID;
	TSoftObjectPtr<AActor> POIActor;
	// TTuple<> POIInfo;

	//got info from POIActor
	UPROPERTY(BlueprintReadOnly)
	TArray<FName> Tags;
	UPROPERTY(BlueprintReadOnly)
	FTransform Transform;
	UPROPERTY(BlueprintReadOnly)
	int StyleIndex = 999;
	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<AActor> POIActorClass;

	UPROPERTY()
	bool bIsVisible = false;
	
	
	
	FString GetInfo() const
	{
		
		return FString::Printf(TEXT(
			"{ \"UID\": \"%s\", \"Tags\": [\"%s\"], \"Transform\": \"%s\", \"StyleIndex\": %d, \"POIActorClass\": \"%s\" }"),
			*FString::FromInt(UID),*FString::Join(Tags, TEXT("\",\"")), *Transform.ToString(), StyleIndex, *POIActorClass->GetName());
	}




};

UCLASS(Blueprintable)
class ENHANCEDPOI_API UPOIHub : public UObject
{
	GENERATED_BODY()

public:
	UPOIHub();

	UFUNCTION(BlueprintCallable)
	FPOIObjectsInfo GetPOIInfo(const FName UID);

	UFUNCTION()
	AActor* GetPOIFast(FName UID);
	
	void RegisterPOI(FName UID, const AActor* POIActor);

private:
	UPROPERTY()
	TMap<FName,TSoftObjectPtr<AActor>> POICacheMap;

	// todo: using tuple to store the info
	UPROPERTY()
	TArray<FPOIObjectsInfo> POIObjectsPool;	
};
