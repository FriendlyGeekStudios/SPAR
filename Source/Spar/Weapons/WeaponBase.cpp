// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Spar/Core/SparCharacter.h"


void AWeaponBase::Interact_Implementation(AActor* InteractingActor)
{
	if (ASparCharacter* Character = Cast<ASparCharacter>(InteractingActor))
	{
		if (!Character->HasWeapon())
		{
			Character->EquipWeapon(this);
			OnWeaponPickedUp();
		}
	}
}

// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MountPoint = CreateDefaultSubobject<USceneComponent>("Mount Point");
	SetRootComponent(MountPoint);

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SceneComponent->SetupAttachment(RootComponent);
	
	WeaponSprite = CreateDefaultSubobject<UPaperFlipbookComponent>("Weapon Sprite");
	WeaponSprite->SetupAttachment(SceneComponent);

	PickupCollider = CreateDefaultSubobject<UBoxComponent>("Pickup Collider");
	PickupCollider->SetupAttachment(SceneComponent);

}

void AWeaponBase::OnWeaponPickedUp()
{
	PickupCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWeaponBase::OnWeaponDropped()
{
	PickupCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
