// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataDrivenComponent.generated.h"

UENUM(Blueprintable)
enum struct EDataSrcType : uint8
{
	EFromCSV,
	EFromJSON,
	EFromURL
};

// make a datatable struct
// USTRUCT(BlueprintType)
// struct FDataDrivenTable : public FTableRowBase
// {
// 	GENERATED_USTRUCT_BODY()
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "POI | DataDriven")
// 	FName UID;
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "POI | DataDriven")
// 	FString FriendlyName;
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "POI | DataDriven")
// 	FVector Location;
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "POI | DataDriven")
// 	FRotator Rotation;
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "POI | DataDriven")
// 	FVector Scale;
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "POI | DataDriven")
// 	FString Description;
// };



// todo: add cache
/*
 * DataDrivenComponent is a component that can be attached to any actor to get data from different sources;
 * It can be used to load data from UDataTable
 * this is just used for short small data
 *
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ENHANCEDPOI_API UDataDrivenComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDataDrivenComponent();
	UFUNCTION(BlueprintCallable, Category = "DataDriven")
	static bool LoadDataCached(const FFilePath DataSourcePath, TArray<FName>& UIDs); // make a link table from UID
	
	bool DataLoaded;

	UFUNCTION(BlueprintCallable, Category = "DataDriven")
	void UpdateFromDataSrc();

	UPROPERTY(EditAnywhere, Category = "POI | DataDriven")
	TArray<FString> DataFields;
	UPROPERTY()
	TArray<FName> POIUIDArray;
	
	TArray<FName> GetUIDs(){return POIUIDArray;};
	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// UPROPERTY(EditDefaultsOnly, Category = "POI | DataDriven")
	// EDataSrc DataSource = EDataSrc::EFromCSV;

#pragma region Getters
public:
	
	FTransform GetTransform(const FName& UID);
	FVector GetFVectorProperty(const FName& UID,const FName& PropertyName);
	FString GetStringProperty(const FName& UID, const FName& PropertyName);
	
	
#pragma endregion
private:
	
	uint8 Data;
	
	
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Settings, meta = (EditCondition = "LocationAnchor", EditConditionHides))
	TSoftObjectPtr<UDataTable> POIParams;

};
