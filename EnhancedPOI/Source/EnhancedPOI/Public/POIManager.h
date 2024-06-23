// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POIContainer.h"
#include "GameFramework/Actor.h"
#include "POIManager.generated.h"


// enum of poi type
UENUM(BlueprintType)
enum class EPOIType : uint8
{
	E3DWidget  , // this is default 
	ESpawnable
};



UCLASS()
class ENHANCEDPOI_API APOIManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APOIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY()
	TArray<APOIContainer*> POIContainerArray;

	
#pragma region Generation
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "POI | Generation")
	EPOIType POIType;

	
protected:
	UPROPERTY(Blueprintable,BlueprintReadOnly, EditDefaultsOnly)
	class UDataDrivenComponent* DataDrivenComponent;



	// todo: construction scripts
	bool GeneratePOIs();

#pragma endregion

	
#pragma region LocationAdjustment
public:
	UFUNCTION(BlueprintCallable, Category = "DataDriven")
	bool UpdateActorProperty(const FName& PropertyName);

protected:


	// assume the POIContainerArray is already exsited
	UFUNCTION(BlueprintCallable, Category = "POI | Location")
	void AnchorPOILocation();

private:
	TMap<FName,FVector> POILocationMap;
	
#pragma endregion
};
