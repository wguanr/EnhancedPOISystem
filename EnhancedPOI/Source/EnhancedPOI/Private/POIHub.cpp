// Fill out your copyright notice in the Description page of Project Settings.


#include "POIHub.h"


FPOIObjectsInfo::FPOIObjectsInfo(TSoftObjectPtr<AActor> POI)
{
	// set info
	UID = POI.Get()->GetUniqueID();
	Tags = POI.Get()->Tags;
	
	Transform = POI.Get()->GetTransform();
	StyleIndex = 999;

	bIsVisible = !POI.Get()->IsHidden();
	
	POIActorClass = POI.Get()->GetClass();
	POIActor = POI;

	
}

FPOIObjectsInfo::~FPOIObjectsInfo()
{
}

UPOIHub::UPOIHub()
{
	POIObjectsPool = TArray<FPOIObjectsInfo>();
	POICacheMap = TMap<FName, TSoftObjectPtr<AActor>>();
}

FPOIObjectsInfo UPOIHub::GetPOIInfo(const FName UID)
{
	// todo : ????
	return FPOIObjectsInfo(GetPOIFast(UID));
}

AActor* UPOIHub::GetPOIFast(FName UID)
{
	TSoftObjectPtr<AActor> POIActor = 
	*POICacheMap.Find(UID);

	
	if (POIActor.IsValid())
	{
		return POIActor.Get();
	}
	return nullptr;
}

void UPOIHub::RegisterPOI(FName UID, const AActor* POIActor)
{
	
	POICacheMap.Add(UID, POIActor);
	POIObjectsPool.Add( FPOIObjectsInfo(POIActor));
}
