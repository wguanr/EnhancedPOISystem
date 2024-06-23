// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "POIContainer.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogPOIContainer, Log, All);

// class UCameraComponent;
/** todo: 1. 添加聚类分析功能
 * 
 */
UCLASS(Abstract)
class ENHANCEDPOI_API APOIContainer : public AActor
{
	GENERATED_BODY()
	
public:
	APOIContainer();
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "POI | Adjustments")
	bool bDefaultHiddenPOI = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Settings)
	bool bAutoActivate;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Settings)
	bool bOnDebug;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "POI | Adjustments")
	bool bLocationAnchor;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Settings)
	FName CustomUID = "CustomName&Tag";

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText Title = FText::FromString(TEXT("MainTitle"));
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText Description = FText::FromString(TEXT("Description"));
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLinearColor ThemeColor = FLinearColor::White;
	
	virtual void POIShow();
	virtual void POIHide();

	UFUNCTION(BlueprintCallable, Category = Settings)
	FString GetCallBackMessage();


	
protected:
	UPROPERTY()
	TObjectPtr<UObject> POIObject;
	


private:
	UPROPERTY()
	FString CallbackMessage = "Callback Message";



#pragma region CameraViewOperations
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void SetFocus(const float BlendTime,const EViewTargetBlendFunction BlendFunction);
	UFUNCTION(BlueprintCallable)
	void ResetFocus();

	
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UCameraComponent* POICameraComponent;

	UFUNCTION(BlueprintCallable)
	FVector GetPOICameraViewLocation() const;
	UFUNCTION(BlueprintCallable)
	FVector GetPOICameraViewRotation() const;
	
#pragma endregion

	
};
