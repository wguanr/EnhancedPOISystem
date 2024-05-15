// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"
#include "POIWidget.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATestActor::ATestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APOIWidget::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		APOIWidget* POIWidget = Cast<APOIWidget>(Actor);
		if (POIWidget)
		{
			POIWidget->POIShow();
			UE_LOG(LogTemp, Warning, TEXT("Found POIWidget: %s"), *POIWidget->GetPathName());
		}
	}

	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

