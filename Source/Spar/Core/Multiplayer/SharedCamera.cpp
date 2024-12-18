// Fill out your copyright notice in the Description page of Project Settings.


#include "SharedCamera.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Spar/Core/SparGameMode.h"


// Sets default values
ASharedCamera::ASharedCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ViewTarget = CreateDefaultSubobject<USceneComponent>("View Target");
	SetRootComponent(ViewTarget);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(ViewTarget);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ASharedCamera::BeginPlay()
{
	Super::BeginPlay();
	ASparGameMode* GameMode = Cast<ASparGameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameMode))
	{
		GameMode->OnNewPlayerJoined.AddUniqueDynamic(this, &ASharedCamera::OnPlayerJoined);
	}
}

void ASharedCamera::OnPlayerJoined(APawn* NewPlayer)
{
	Players.AddUnique(NewPlayer);
}

// Called every frame
void ASharedCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update our View Target with the average location between all players
	FVector OriginLocation = ViewTarget->GetComponentLocation();
	FVector TargetLocation = UGameplayStatics::GetActorArrayAverageLocation(Players);

	FVector IntermediateLocation = FMath::Lerp(OriginLocation, TargetLocation, TweenSpeed);
	ViewTarget->SetWorldLocation(IntermediateLocation);

	float LargestDistance = 0.0f;
	for (int i = 0; i < Players.Num() - 1; i++)
	{
		AActor* CurrentActor = Players[i];
		for (int j = i + 1; j < Players.Num(); j++)
		{
			float Distance = CurrentActor->GetDistanceTo(Players[j]);
			LargestDistance = FMath::Max(LargestDistance, Distance);
		}
	}

	//
	float NewCameraWidth = FMath::Clamp(LargestDistance, MinViewWidth, MaxViewWidth) + ViewOffset;
	Camera->SetOrthoWidth(NewCameraWidth);
}
