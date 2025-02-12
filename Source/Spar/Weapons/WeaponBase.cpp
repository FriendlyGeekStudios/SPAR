// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	WeaponSprite = CreateDefaultSubobject<UPaperFlipbookComponent>("Weapon Sprite");
	WeaponSprite->SetupAttachment(RootComponent);

	PickupCollider = CreateDefaultSubobject<UBoxComponent>("Pickup Collider");
	PickupCollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponBase::OnPickupOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
