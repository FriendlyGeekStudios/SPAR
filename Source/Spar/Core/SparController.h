﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "SparController.generated.h"

class ASparCharacter;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class SPAR_API ASparController : public APlayerController
{
	GENERATED_BODY()

	virtual void SetupInputComponent() override;
	virtual void SetupInactiveStateInputComponent(UInputComponent* InComponent) override;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginInactiveState() override;
	virtual void EndInactiveState() override;

private:
	void Move(const FInputActionValue& Value);

	void JumpStarted();
	void JumpEnded();

	void Attack();

	void OnJoinGameTriggered();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* GameplayMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* JoinGameMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* JoinGameAction;

	UPROPERTY()
	ASparCharacter* ControlledCharacter;
};
