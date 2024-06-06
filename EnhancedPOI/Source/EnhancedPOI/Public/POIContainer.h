// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataDrivenComponent.h"
#include "GameFramework/Actor.h"
#include "POIContainer.generated.h"


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
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Settings)
	bool bDefaultHiddenPOI;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Settings)
	bool bAutoActivate;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Settings)
	bool bOnDebug;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = Settings)
	bool bDataDriven;

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
	
	UPROPERTY(Blueprintable,BlueprintReadOnly, EditDefaultsOnly)
	UDataDrivenComponent* DataDrivenComponent;


private:
	UPROPERTY()
	FString CallbackMessage = "Callback Message";

	void SetDataDrivenComponent();


#pragma region CameraViewOperations
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void SetFocus(const float BlendTime,const EViewTargetBlendFunction BlendFunction);
	UFUNCTION(BlueprintCallable)
	void ResetFocus();

	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Settings)
	bool bAttachCamera;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Components)
	class UCameraComponent* POICameraComponent;

	UFUNCTION(BlueprintCallable)
	FVector GetPOICameraViewLocation() const;
	UFUNCTION(BlueprintCallable)
	FVector GetPOICameraViewRotation() const;
	
#pragma endregion

	
};
