// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"

#include "DebugSparCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class APaper2DCharacter;

/**
 * 
 */
UCLASS()
class SPAR_API ADebugSparCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ADebugSparCharacter();

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> CameraComponent;
};
