// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataDrivenComponent.generated.h"

UENUM(Blueprintable)
enum struct EDataSrc : uint8
{
	EFromCSV,
	EFromJSON,
	EFromURL
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ENHANCEDPOI_API UDataDrivenComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDataDrivenComponent();
	UFUNCTION(BlueprintCallable, Category = "DataDriven")
	void LoadData(const EDataSrc DataSource); // make a link table from UID
	UFUNCTION(BlueprintCallable, Category = "DataDriven")
	void UpdateFromDataSrc();
	UFUNCTION(BlueprintCallable, Category = "DataDriven")
	bool UpdateActorProperty(const FName& PropertyName);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// UPROPERTY(EditDefaultsOnly, Category = "POI | DataDriven")
	// EDataSrc DataSource = EDataSrc::EFromCSV;

	FTransform GetTransform(const FName& UID);
	FVector GetFVectorProperty(const FName& UID,const FName& PropertyName); // location, rotation, scale .etc
	FString GetStringProperty(const FName& UID, const FName& PropertyName);

	
	
private:
	
	void CullNullData();
	
	uint8 Data;
	
	void LoadDataFromCSV();
	void LoadDataFromJSON();
	void LoadDataFromURL();
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	
};
