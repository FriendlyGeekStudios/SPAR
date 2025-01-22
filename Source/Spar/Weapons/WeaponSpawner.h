// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponSpawner.generated.h"

UCLASS()
class SPAR_API AWeaponSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	int WeaponSelectionRating = 0; // 0 = common, 1 = uncommon, 2 = rare, 3 = legendary

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* WeaponPoolDataTable = nullptr;
};
