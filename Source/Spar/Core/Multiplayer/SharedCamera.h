// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SharedCamera.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SPAR_API ASharedCamera : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASharedCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPlayerJoined(APawn* NewPlayer);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* ViewTarget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TweenSpeed = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxViewWidth = 1200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinViewWidth = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ViewOffset = 100.f;

	UPROPERTY()
	TArray<AActor*> Players{};
};
