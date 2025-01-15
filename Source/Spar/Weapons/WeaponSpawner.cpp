// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSpawner.h"

#include "WeaponInfo.h"


// Sets default values
AWeaponSpawner::AWeaponSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeaponSpawner::BeginPlay()
{
	Super::BeginPlay();

	
	// Pick a random weapon from a pool of weapons, based on a rating status
	check(WeaponPoolDataTable != nullptr);

	TArray<FWeaponInfo> Weapons;
	WeaponPoolDataTable->ForeachRow<FWeaponInfo>("", [&](const FName& Key, const FWeaponInfo& Value)
	{
		if (Value.WeaponRating == WeaponSelectionRating)
		{
			Weapons.Add(Value);
		}
	});

	int WeaponIndex = FMath::RandRange(0, Weapons.Num() - 1);

	auto SelectedWeapon = Weapons[WeaponIndex];

	GEngine->AddOnScreenDebugMessage(WeaponSelectionRating, 10.0f, FColor::Red, SelectedWeapon.Name);

	
}

// Called every frame
void AWeaponSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

