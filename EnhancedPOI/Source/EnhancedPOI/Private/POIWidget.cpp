// Fill out your copyright notice in the Description page of Project Settings.


#include "POIWidget.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"



// Sets default values
APOIWidget::APOIWidget()
{
	
	PrimaryActorTick.bCanEverTick = true;
	// 1: set defaults

	// RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);


	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	WidgetComponent->SetVisibility(true);
	WidgetComponent->Activate(bAutoActivate);
	
	// 2: set component
	WidgetComponent->InitWidget();
	
	if (UserDefinedWidgetClass)
	{
		WidgetComponent->SetWidgetClass(UserDefinedWidgetClass);
	}
	else
	{
		// todo: add default widget class
	}

	
	
}


// Called when the game starts or when spawned
void APOIWidget::BeginPlay()
{
	Super::BeginPlay();
	
	
	if (APlayerController* CPC = GetWorld()->GetFirstPlayerController())
	{
		EnableInput(CPC);
		FInputModeGameAndUI InputMode;
		
		// InputMode.SetWidgetToFocus(WidgetComponent->GetWidget()->TakeWidget());
		CPC->SetInputMode(InputMode);
		CPC->bEnableClickEvents = true;
	}

	if (bAddCollision && POICollisionComponentClass)
	{
		if (CustomBoxExtent.IsZero())
		{
			CustomBoxExtent = GetComponentsBoundingBox(false,false).GetExtent();
		}
		
		
		UShapeComponent* POICollision = NewObject<UShapeComponent>(this,POICollisionComponentClass);
	
		POICollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		POICollision->RegisterComponent();
		POICollision->OnClicked.AddDynamic(this,&APOIWidget::OnCollisionClicked);
		POICollision->OnBeginCursorOver.AddDynamic(this,&APOIWidget::OnCollisionBeginCursorOver);
		POICollision->OnEndCursorOver.AddDynamic(this,&APOIWidget::OnCollisionEndCursorOver);
		POICollision->SetCollisionProfileName(FName("BlockAll"));
#if WITH_EDITOR
		POICollision->SetVisibility(true);
		POICollision->SetHiddenInGame(false);
#endif
		
		if (UBoxComponent* Box = Cast<UBoxComponent>(POICollision))
		{
			Box->SetBoxExtent(CustomBoxExtent);
			BoxCollisionComponent = Box; // for tick rotation
		}
		if (USphereComponent* Sphere = Cast<USphereComponent>(POICollision))
		{
			Sphere->SetSphereRadius(CustomBoxExtent.Size());
		}
		if (UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(POICollision))
		{
			Capsule->SetCapsuleSize(CustomBoxExtent.Size(),CustomBoxExtent.Z);
		}
		
		

	}

	

}

void APOIWidget::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	Tags.AddUnique(FName("POI.Widget"));
	if (!UserDefinedWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Widget Class Defined"));
		return;
	}
	// WidgetComponent->InitWidget();

	
	WidgetComponent->SetWidgetClass(UserDefinedWidgetClass); //  for begin play
	if (UserCustomWidgetObject) // so we can see in editor
	{
		WidgetComponent->SetWidget(UserCustomWidgetObject);
		POIObject = UserCustomWidgetObject; // but useless, can't get interface
	}
	else
	{
		UUserWidget* MyWidget = CreateWidget<UUserWidget>(GetWorld(), UserDefinedWidgetClass);
		
		WidgetComponent->SetWidget(MyWidget);
	}
	WidgetComponent->UpdateWidget();

	
}



#pragma region autoAddCollision
void APOIWidget::OnCollisionClicked_Implementation(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Clicked %s"), *Title.ToString()));
}

void APOIWidget::OnCollisionBeginCursorOver_Implementation(UPrimitiveComponent* TouchedComponent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("BeginCursorOver %s"), *Title.ToString()));

}

void APOIWidget::OnCollisionEndCursorOver_Implementation(UPrimitiveComponent* TouchedComponent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("BeginCursorOver %s"), *Title.ToString()));

}

#pragma endregion

// Called every frame
void APOIWidget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	if (!WidgetComponent) return;
	
	const FVector CameraLocation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	const FRotator LookAtRotation = FRotationMatrix::MakeFromX(CameraLocation - GetActorLocation()).Rotator();
	
	switch (WidgetFacingStyle)
	{
	case EWidgetFacing::EFaceModeA:
		WidgetComponent->SetWorldRotation(FRotator (0,LookAtRotation.Yaw,0));
		if (BoxCollisionComponent) BoxCollisionComponent->SetWorldRotation(FRotator (0,LookAtRotation.Yaw,0));
		break;
	case EWidgetFacing::EFaceModeB:
		WidgetComponent->SetWorldRotation(FRotator (LookAtRotation.Pitch,round((LookAtRotation.Yaw+180)/360)*180-90,0));
		if (BoxCollisionComponent) BoxCollisionComponent->SetWorldRotation(FRotator (LookAtRotation.Pitch,round((LookAtRotation.Yaw+180)/360)*180-90,0));
		break; 
	case EWidgetFacing::EFaceModeC:
		WidgetComponent->SetWorldRotation(LookAtRotation);
		if (BoxCollisionComponent) BoxCollisionComponent->SetWorldRotation(LookAtRotation);

		break;
	default:
		WidgetComponent->SetWorldRotation(FRotator (0,LookAtRotation.Yaw,0));
		if (BoxCollisionComponent) BoxCollisionComponent->SetWorldRotation(FRotator (0,LookAtRotation.Yaw,0));
		break;
	}

}

#pragma region WidgetSettings



#pragma endregion
#if WITH_EDITOR
void APOIWidget::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property!=nullptr)
	{
		const FName ThisProperty = PropertyChangedEvent.GetPropertyName();
		
		if (ThisProperty == GET_MEMBER_NAME_CHECKED(APOIWidget, CustomUID) || ThisProperty == GET_MEMBER_NAME_CHECKED(APOIWidget, Title))
		{
			// auto x = FString::Printf("%ls_%ls", *PMIContent.Title.ToString(),*CustomUID.ToString());
			SetActorLabel("POI_"+Title.ToString()+"_"+CustomUID.ToString());
		}
		
		UpdateComponents();
		
	}

}

#endif
	


void APOIWidget::UpdateComponents() const
{
	WidgetComponent->SetWidgetClass(UserDefinedWidgetClass);
	WidgetComponent->UpdateWidget();
	
}

// why to use this?
FString APOIWidget::GenerateUID() const
{
	FDateTime Now = FDateTime::Now();
	return FString::Printf(TEXT("%s_%s"), *Now.ToString(), *Title.ToString());
}






