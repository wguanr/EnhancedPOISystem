// Fill out your copyright notice in the Description page of Project Settings.


#include "POIContainer.h"
#include "POIEventInterface.h"
#include "POIHub.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"





APOIContainer::APOIContainer()
{
	POIObject = nullptr;
	DataDrivenComponent = nullptr;
	POICameraComponent = nullptr;
	PrimaryActorTick.bCanEverTick = true;
	bDataDriven = false;
	bAttachCamera = false;
	bDefaultHiddenPOI = false;
	bAutoActivate = true;
	bOnDebug = false;
	CallbackMessage = TEXT("POIContainer");

	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	DataDrivenComponent = CreateDefaultSubobject<UDataDrivenComponent>("DataDrivenComponent");

	
}

void APOIContainer::BeginPlay()
{
	Super::BeginPlay();
	SetActorHiddenInGame(bDefaultHiddenPOI);
	if (!CustomUID.IsEqual(TEXT("CustomName&Tag")))
	{
		// const auto x = FString::Printf("POI.UID.%ls", *CustomUID.ToString());
		Tags.AddUnique(CustomUID);
		
	}

	// cache the info to the POIHub
	TArray<UObject*> Objects;
	GetObjectsOfClass(UPOIHub::StaticClass(),Objects,false);
	UPOIHub* POIHub;
	if (Objects.Num() == 0)
	{
		POIHub = NewObject<UPOIHub>();
		POIHub->AddToRoot();
	}
	else
	{
		POIHub = Cast<UPOIHub>(Objects[0]);
	}
	
	POIHub->RegisterPOI(CustomUID,this);

	///component setting

	if (bDataDriven)
	{
		
	}
	if (bAttachCamera)
	{
		
	}
	/// debug test///
	/// 
	if (bOnDebug)
	{
		
		DrawDebugBox(GetWorld(), GetActorLocation(), FVector(50, 50, 50), FColor::Green, true, -1, 0, 2);
		// check if the poi object is set correctly
		if (!POIObject)
		{
			UE_LOG(LogTemp, Error, TEXT("POIObject is not set correctly"));
		}
	}
	
	
	
}

void APOIContainer::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// SetDataDrivenComponent();

	if (bAttachCamera)
	{
		POICameraComponent = Cast<UCameraComponent>(AddComponentByClass(UCameraComponent::StaticClass(),
			false,FTransform::Identity,false));
		POICameraComponent->SetupAttachment(RootComponent);
		
	}
	else
	{
		if (POICameraComponent)
		{
			POICameraComponent->DestroyComponent();
			POICameraComponent = nullptr;
			
		}
	}
	POICameraComponent->Activate(bAutoActivate);
	DataDrivenComponent->Activate(bAutoActivate);
	
}

FString APOIContainer::GetCallBackMessage()
{
	
	return CallbackMessage;
}

void APOIContainer::POIShow()
{
	SetActorHiddenInGame(false);
	
	if (POIObject && POIObject->Implements<UPOIEventInterface>())
	{
		IPOIEventInterface::Execute_OnPOIShow(POIObject);
	}
	
}

void APOIContainer::POIHide()
{
	if (!POIObject->IsValidLowLevel()) return;
	
	if (POIObject->Implements<UPOIEventInterface>())
	{
		IPOIEventInterface::Execute_OnPOIHide(POIObject);
	}
	else
	{
		SetActorHiddenInGame(true);
		
	}
	
}

#pragma region CameraViewOperations
void APOIContainer::SetFocus(const float BlendTime = 2.f,const EViewTargetBlendFunction BlendFunction = VTBlend_EaseIn)
{
	APlayerCameraManager* CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FViewTargetTransitionParams Params;
	Params.BlendTime = BlendTime;
	// Params.bLockOutgoing = true;
	Params.BlendExp = 2.0f;
	Params.BlendFunction = BlendFunction;
	
	if (AActor* ViewTarget = Cast<AActor>(POIObject))
	{
		CameraManager->SetViewTarget(ViewTarget,Params);
		// reset the view target
		
		return;
	}
	CameraManager->SetViewTarget(this,Params);
}

void APOIContainer::ResetFocus()
{
	APlayerCameraManager* CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	CameraManager->SetViewTarget(GetWorld()->GetFirstPlayerController()->GetPawn());
	
}

FVector APOIContainer::GetPOICameraViewLocation() const
{
	check(POICameraComponent);
	FMinimalViewInfo VInfo;
	POICameraComponent->GetCameraView(0,VInfo);
	return VInfo.Location;
}

FVector APOIContainer::GetPOICameraViewRotation() const
{
	check(POICameraComponent);
	FMinimalViewInfo VInfo;
	POICameraComponent->GetCameraView(0,VInfo);
	
	return VInfo.Rotation.Vector();
}

#pragma endregion
// better to make this in constructor
void APOIContainer::SetDataDrivenComponent()
{
	if (bDataDriven)
	{
		if (DataDrivenComponent) return;
		
		DataDrivenComponent = Cast<UDataDrivenComponent>(AddComponentByClass(
			UDataDrivenComponent::StaticClass(),false,FTransform::Identity,false));
		DataDrivenComponent->Activate(bAutoActivate);
		
	}
	else
	{
		if (DataDrivenComponent)
		{
			DataDrivenComponent->DestroyComponent();
			DataDrivenComponent = nullptr;
		}
	}
	
}
