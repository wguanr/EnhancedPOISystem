// Fill out your copyright notice in the Description page of Project Settings.


#include "DataDrivenComponent.h"

#include "ImageUtils.h"
#include "Misc/FileHelper.h"


// Sets default values for this component's properties
UDataDrivenComponent::UDataDrivenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UDataDrivenComponent::LoadDataCached(const FFilePath DataSourcePath, TArray<FName>& UIDs)
{
	EDataSrcType DataSourceType = EDataSrcType::EFromCSV;
	FString FileName;
	FString FileExtension;
	//whether the file is 
	if (!FPaths::FileExists(DataSourcePath.FilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("[DataDrivenComponent] File not found: %s"), *DataSourcePath.FilePath);
		return false;
	}
	TArray<FString> DataStr;
	if(FFileHelper::LoadFileToStringArray(DataStr, *DataSourcePath.FilePath))
	{
		FString DataHeader = DataStr[0];
		DataStr.RemoveAt(0);
		TIterator<TArray<FString>> It(DataStr);
		while (It)
		{
			//parse the data
			FString Line = *It;
			//parse the line
			TArray<FString> LineData;
			Line.ParseIntoArray(LineData, TEXT(","), false);
			//parse the line data
			FName UID = *LineData[0];
			UIDs.Add(UID);
			//parse the line data as X Y Z
			FVector Location = FVector(FCString::Atof(*LineData[1]), FCString::Atof(*LineData[2]), FCString::Atof(*LineData[3]));
			FString Description = LineData[10];

			//todo: serialize the data and cache it
			++It;
		}
	}

	
	
	
	
	return true;
}

void UDataDrivenComponent::UpdateFromDataSrc()
{
}



FTransform UDataDrivenComponent::GetTransform(const FName& UID)
{
	return FTransform();
}

FVector UDataDrivenComponent::GetFVectorProperty(const FName& UID, const FName& PropertyName)
{
	return FVector();
}

FString UDataDrivenComponent::GetStringProperty(const FName& UID, const FName& PropertyName)
{
	return FString();
}

// Called when the game starts
void UDataDrivenComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GEngine->AddOnScreenDebugMessage(11, 5.f, FColor::Green, TEXT("[DataDrivenComponent] BeginPlay"));
}


// Called every frame
void UDataDrivenComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

