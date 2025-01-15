#pragma once

#include "WeaponSpawner.generated.h"

// Okay, how will this work?
UCLASS()
class AWeaponSpawner : public AActor
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
};
