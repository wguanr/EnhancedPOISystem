// Fill out your copyright notice in the Description page of Project Settings.


#include "POIManager.h"
#include "DataDrivenComponent.h"
#include "POIContainer.h"

// Sets default values
APOIManager::APOIManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DataDrivenComponent = nullptr;
	//create a DataDrivenComponent
	
	DataDrivenComponent = CreateDefaultSubobject<UDataDrivenComponent>(TEXT("DataDrivenComponent"));

}

// Called when the game starts or when spawned
void APOIManager::BeginPlay()
{
	Super::BeginPlay();
	// get attached single POI actor
	TArray<AActor*> OutPOIContainerArray;
	GetAttachedActors(OutPOIContainerArray);
	for (AActor*& POIContainerActor : OutPOIContainerArray)
	{
		POIContainerArray.AddUnique(Cast<APOIContainer>(POIContainerActor));
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("POIContainerArray: %d"), POIContainerArray.Num()));
}

// Called every frame
void APOIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



bool APOIManager::GeneratePOIs()
{
	if (!DataDrivenComponent->DataLoaded)
	{
		UE_LOG(LogPOIContainer, Error, TEXT("[Error] DataDrivenComponent is not loaded"));
		return false;
	}
	
	return true;
}

bool APOIManager::UpdateActorProperty(const FName& PropertyName)
{
	return true;
}
void APOIManager::AnchorPOILocation()
{
	//validate poicontainer array and datatable
	if (POIContainerArray.Num() == 0 || !DataDrivenComponent  )
	{
		UE_LOG(LogPOIContainer, Error, TEXT("[Error] POIContainerArray is empty"));
		return;
	}
	
	for ( const FName &_UID : DataDrivenComponent->GetUIDs())
	{
		//get the container
		
		for (APOIContainer*& POIContainer : POIContainerArray)
		{
			if (POIContainer->CustomUID != _UID) continue;
			
			if (POIContainer->bLocationAnchor)
			{
				FVector Location = DataDrivenComponent->GetFVectorProperty(_UID, "Location");
			
				POIContainer->SetActorLocation(Location);
			}
			
			
				
			
		}
	
	
		
	}
	
}
