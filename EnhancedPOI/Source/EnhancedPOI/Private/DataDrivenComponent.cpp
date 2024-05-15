// Fill out your copyright notice in the Description page of Project Settings.


#include "DataDrivenComponent.h"


// Sets default values for this component's properties
UDataDrivenComponent::UDataDrivenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UDataDrivenComponent::LoadData(const EDataSrc DataSource)
{
}

void UDataDrivenComponent::UpdateFromDataSrc()
{
}

bool UDataDrivenComponent::UpdateActorProperty(const FName& PropertyName)
{
	return true;
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

void UDataDrivenComponent::CullNullData()
{
}

void UDataDrivenComponent::LoadDataFromCSV()
{
}

void UDataDrivenComponent::LoadDataFromJSON()
{
}

void UDataDrivenComponent::LoadDataFromURL()
{
}


// Called when the game starts
void UDataDrivenComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("[DataDrivenComponent] BeginPlay"));
}


// Called every frame
void UDataDrivenComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

