// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "POIContainer.h"
#include "POIEventInterface.h"
#include "POIWidget.generated.h"




UENUM(Blueprintable)
enum class EWidgetFacing : uint8
{
	EFaceModeA UMETA(DisplayName="Z Aixs"),
	EFaceModeB UMETA(DisplayName="Y Aixs"),
	EFaceModeC UMETA(DisplayName="Face 720")

};

// don't need that? default is sphere
// UENUM(Blueprintable)
// enum class EPOIRootComponent : uint8
// {
// 	EBox UMETA(DisplayName="BoxComponent",ComponentClass=UBoxComponent),
// 	ESphere UMETA(DisplayName="SphereComponent",ComponentClass=UCapsuleComponent)
// };


UCLASS(Blueprintable)
class ENHANCEDPOI_API APOIWidget : public APOIContainer
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APOIWidget();
	
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	

	#pragma region WidgetSettings
protected:
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = Settings)
	TSubclassOf<UUserWidget> UserDefinedWidgetClass;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = POIContainer)
	FText Subtitle = FText::FromString(TEXT("Subtitle"));
		
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = POIContainer)
	UTexture2D* ImageBG;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly, Category = Settings)
	class UWidgetComponent* WidgetComponent;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = Settings)
	EWidgetFacing WidgetFacingStyle;


private:
	UPROPERTY()
	UUserWidget* UserCustomWidgetObject;
#pragma endregion

	#pragma region autoAddCollision
	
protected:

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = Settings)
	bool bAddCollision = false;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "POI | Collision",meta=(EditCondition="bAddCollision",EditConditionHides))
	TSubclassOf<UShapeComponent> POICollisionComponentClass;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "POI | Collision",meta=(EditCondition="bAddCollision",EditConditionHides))
	FVector CustomBoxExtent = FVector::Zero();

	// this is to simulate the button pressed , hovered and clicked
	UFUNCTION(BlueprintImplementableEvent)
	void OnCollisionClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	void OnCollisionClicked_Implementation(UPrimitiveComponent* TouchedComponent , FKey ButtonPressed);

	UFUNCTION(BlueprintImplementableEvent)
	void OnCollisionBeginCursorOver(UPrimitiveComponent* TouchedComponent);
	void OnCollisionBeginCursorOver_Implementation(UPrimitiveComponent* TouchedComponent);

	UFUNCTION(BlueprintImplementableEvent)
	void OnCollisionEndCursorOver(UPrimitiveComponent* TouchedComponent);
	void OnCollisionEndCursorOver_Implementation(UPrimitiveComponent* TouchedComponent);

private:
	UPROPERTY()
	UShapeComponent* BoxCollisionComponent;
#pragma endregion	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

#if  WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	void UpdateComponents() const;


	FString GenerateUID() const;


};
