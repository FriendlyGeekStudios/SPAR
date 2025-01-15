#pragma once

#include "WeaponInfo.generated.h"

USTRUCT(BlueprintType)
struct FWeaponInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WeaponRating = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* WeaponClass;
};
