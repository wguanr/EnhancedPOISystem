// Fill out your copyright notice in the Description page of Project Settings.


#include "POISpawnable.h"


// Sets default values
APOISpawnable::APOISpawnable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	POITransform = FTransform();
	
}

void APOISpawnable::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (bManualAttach)
	{
		GetWorld()->SpawnActor<AActor>(POIActorClass, POITransform);
		
	}
}

// Called when the game starts or when spawned
void APOISpawnable::BeginPlay()
{
	Super::BeginPlay();
	
	if (POIActorClass)
	{
		AActor* POIActor = GetWorld()->SpawnActor<AActor>(POIActorClass, POITransform);
		POIActor->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		POIObject = POIActor;
	}
}

// Called every frame
void APOISpawnable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

