// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SparGameMode.generated.h"

class ASharedCamera;
class ASparCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewPlayerJoined, APawn*, NewPlayer);

/**
 * 
 */
UCLASS()
class SPAR_API ASparGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void SpawnNewPlayer(APlayerController* PlayerController);

	UPROPERTY(BlueprintAssignable)
	FOnNewPlayerJoined OnNewPlayerJoined;

	void RegisterNewPlayer();

private:
	void GatherAllPlayerStarts();
	APlayerStart* GetPlayerStart(int32 PlayerIndex);
	UFUNCTION()
	void OnPlayerRegistered(APlayerController* Controller);
	APlayerController* GetOrSpawnNewPlayerController(int32 PlayerIndex);
	void GatherSharedCamera();

	TArray<APlayerStart*> PlayerStarts{};

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ASparCharacter> GameplayCharacterClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ASharedCamera* SharedCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<APlayerController*, bool> RegisteredPlayers; // bool if the player is alive
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<APlayerController*, int32> PlayerScores; // bool if the player is alive
};
