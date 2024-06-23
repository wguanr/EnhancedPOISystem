// Fill out your copyright notice in the Description page of Project Settings.


#include "POIContainer.h"
#include "POIEventInterface.h"
#include "POIHub.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"


DEFINE_LOG_CATEGORY (LogPOIContainer);


APOIContainer::APOIContainer()
{
	POIObject = nullptr;

	POICameraComponent = nullptr;
	PrimaryActorTick.bCanEverTick = true;

	bDefaultHiddenPOI = false;
	bAutoActivate = true;
	bOnDebug = false;
	CallbackMessage = TEXT("POIContainer");

	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	// DataDrivenComponent = CreateDefaultSubobject<UDataDrivenComponent>("DataDrivenComponent");

	
}

void APOIContainer::BeginPlay()
{
	Super::BeginPlay();
	// set the default UProperties
	SetActorHiddenInGame(bDefaultHiddenPOI);
	if (!CustomUID.IsEqual(TEXT("CustomName&Tag")))
	{
		Tags.AddUnique(CustomUID);
	}
	bLocationAnchor? GetRootComponent()->SetMobility(EComponentMobility::Movable):GetRootComponent()->SetMobility(EComponentMobility::Static);
	
	UCameraComponent* CameraComponent =Cast<UCameraComponent>( GetComponentByClass(UCameraComponent::StaticClass()));
	POICameraComponent = CameraComponent;
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

	

	
	if (UCameraComponent* POICam = Cast<UCameraComponent>( GetComponentByClass(UCameraComponent::StaticClass())))
	{
		POICameraComponent = POICam;
		UE_LOG(LogPOIContainer, Log, TEXT("[Init] POICameraComponent is set correctly"));
	}
	/// debug test///
	/// 
	if (bOnDebug)
	{
		
		DrawDebugBox(GetWorld(), GetActorLocation(), FVector(50, 50, 50), FColor::Green, true, -1, 0, 2);
		// check if the poi object is set correctly
		if (!POIObject)
		{
			UE_LOG(LogPOIContainer, Error, TEXT("POIObject is not set correctly"));
		}
	}
	
	
	
}

void APOIContainer::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
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
	if (!IsValid(POICameraComponent))
	{
		UE_LOG(LogPOIContainer, Error, TEXT("[Init] POICameraComponent is not set correctly"));
		return;
	}
	APlayerCameraManager* CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FViewTargetTransitionParams Params;
	Params.BlendTime = BlendTime;
	// Params.bLockOutgoing = true;
	Params.BlendExp = 2.0f;
	Params.BlendFunction = BlendFunction;

	// align the camera view to POICameraComponent
	if (IsValid( Cast<AActor>(POIObject)->GetComponentByClass(UCameraComponent::StaticClass())))
	{
		CameraManager->SetViewTarget(Cast<AActor>(POIObject),Params);
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
	POICameraComponent->GetCameraView(this->GetWorld()->GetDeltaSeconds(),VInfo);
	return VInfo.Location;
}

FVector APOIContainer::GetPOICameraViewRotation() const
{
	check(POICameraComponent);
	FMinimalViewInfo VInfo;
	POICameraComponent->GetCameraView(this->GetWorld()->GetDeltaSeconds(),VInfo);
	
	return VInfo.Rotation.Vector();
}

#pragma endregion
// better to make this in constructor

