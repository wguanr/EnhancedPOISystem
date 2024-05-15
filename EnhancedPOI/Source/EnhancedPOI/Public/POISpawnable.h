// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POIContainer.h"
#include "POISpawnable.generated.h"

UCLASS()
class ENHANCEDPOI_API APOISpawnable : public APOIContainer
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APOISpawnable();
	virtual void OnConstruction(const FTransform& Transform) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = POI)
	bool bManualAttach;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = POI)
	TSubclassOf<AActor> POIActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = POI,meta=(EditCondition="bManualAttach",EditConditionHides))
	FTransform POITransform;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
