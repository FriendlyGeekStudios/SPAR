// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"

class UBoxComponent;
class UPaperFlipbookComponent;

UCLASS()
class SPAR_API ATeleporter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATeleporter();

protected:
	UFUNCTION()
	void OnPlayerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPlayerEnterRight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnPlayerEnterLeft(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ClearLastTeleportedActor();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void TeleportPlayerTo(AActor* InActor, const FVector& Destination);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPaperFlipbookComponent> TeleporterFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> RightOutput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> LeftOutput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> RightEntranceCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> LeftEntranceCollider;

	UPROPERTY(EditInstanceOnly)
	TObjectPtr<ATeleporter> DestinationTeleporter = nullptr;

private:
	TWeakObjectPtr<AActor> LastTeleportedActor;
};
