// Fill out your copyright notice in the Description page of Project Settings.


#include "SparGameMode.h"

#include "SparCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Multiplayer/SharedCamera.h"

void ASparGameMode::BeginPlay()
{
	Super::BeginPlay();

	GatherAllPlayerStarts();
	GatherSharedCamera();

	for (int i = 1; i < 4; i++)
	{
		APlayerController* NewPlayerController = GetOrSpawnNewPlayerController(i);
		if (!IsValid(NewPlayerController))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to find Player Controller"))
			continue;
		}

		APlayerStart* PlayerStart = GetPlayerStart(i);
		if (!IsValid(PlayerStart))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to find Player Start"))
			continue;
		}

		FTransform StartTransform = PlayerStart->GetTransform();
		NewPlayerController->SetInitialLocationAndRotation(StartTransform.GetLocation(), StartTransform.Rotator());
	}

	APlayerController* FirstPlayerController = GetOrSpawnNewPlayerController(0);
	if (!IsValid(FirstPlayerController))
	{
		return;
	}

	APlayerStart* FirstPlayerStart = GetPlayerStart(0);
	if (!IsValid(FirstPlayerStart))
	{
		return;
	}

	AActor* FirstPlayerCharacter = GetWorld()->SpawnActor(GameplayCharacterClass, &(FirstPlayerStart->GetTransform()));
	APawn* NewPlayer = Cast<APawn>(FirstPlayerCharacter);
	if (IsValid(NewPlayer))
	{
		FirstPlayerController->Possess(NewPlayer);
		FirstPlayerController->SetViewTargetWithBlend(SharedCamera);
		OnNewPlayerJoined.Broadcast(NewPlayer);
	}
}

void ASparGameMode::SpawnNewPlayer(APlayerController* PlayerController)
{
	APlayerStart* PlayerStart = GetPlayerStart(PlayerController->GetPlatformUserId().GetInternalId());
	if (!IsValid(PlayerStart))
	{
		return;
	}
	AActor* NewCharacterActor = GetWorld()->SpawnActor(GameplayCharacterClass, &(PlayerStart->GetTransform()));
	APawn* NewPawn = Cast<APawn>(NewCharacterActor);
	if (IsValid(NewPawn))
	{
		PlayerController->Possess(NewPawn);
		PlayerController->SetViewTargetWithBlend(SharedCamera);

		OnNewPlayerJoined.Broadcast(NewPawn);
	}
}

void ASparGameMode::GatherAllPlayerStarts()
{
	TArray<AActor*> RawPlayerStartActors{};
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), RawPlayerStartActors);

	for (AActor* RawPlayerStart : RawPlayerStartActors)
	{
		APlayerStart* PlayerStart = Cast<APlayerStart>(RawPlayerStart);
		if (IsValid(PlayerStart))
		{
			PlayerStarts.Add(PlayerStart);
		}
	}
}

APlayerStart* ASparGameMode::GetPlayerStart(int32 PlayerIndex)
{
	for (APlayerStart* PlayerStart : PlayerStarts)
	{
		int32 PlayerStartTag = FCString::Atoi(*PlayerStart->PlayerStartTag.ToString());
		if (PlayerStartTag == PlayerIndex)
		{
			return PlayerStart;
		}
	}
	return nullptr;
}

APlayerController* ASparGameMode::GetOrSpawnNewPlayerController(int32 PlayerIndex)
{
	APlayerController* OutPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), PlayerIndex);
	if (!IsValid(OutPlayerController))
	{
		// Create a new Player Controller
		OutPlayerController = UGameplayStatics::CreatePlayer(GetWorld(), PlayerIndex);
	}
	return OutPlayerController;
}

void ASparGameMode::GatherSharedCamera()
{
	TArray<AActor*> CameraActors{};
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASharedCamera::StaticClass(), CameraActors);

	if (CameraActors.Num() == 0)
	{
		// We couldn't find the camera...
		return;
	}

	SharedCamera = Cast<ASharedCamera>(CameraActors[0]);
	if (!IsValid(SharedCamera))
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find Shared Camera. Does it exist in the level?"))
	}
}
