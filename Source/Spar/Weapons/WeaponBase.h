﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spar/Core/Interactable.h"
#include "WeaponBase.generated.h"

class UBoxComponent;
class UPaperFlipbookComponent;

UCLASS()
class SPAR_API AWeaponBase : public AActor, public IInteractable
{
public:
	virtual void Interact_Implementation(AActor* InteractingActor) override;

private:
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

	UFUNCTION(BlueprintImplementableEvent)
	void Attack();

	void OnWeaponPickedUp();
	void OnWeaponDropped();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> MountPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapons)
	TObjectPtr<UPaperFlipbookComponent> WeaponSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapons)
	TObjectPtr<UBoxComponent> PickupCollider;
};
