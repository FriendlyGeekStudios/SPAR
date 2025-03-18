// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "SparController.generated.h"

class ASparCharacter;
class UInputAction;
class UInputMappingContext;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterPossessed, APlayerController*, Controller);

/**
 * 
 */
UCLASS()
class SPAR_API ASparController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;
	virtual void SetupInactiveStateInputComponent(UInputComponent* InComponent) override;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginInactiveState() override;
	virtual void EndInactiveState() override;

	FOnCharacterPossessed OnCharacterPossessed;

private:
	void Move(const FInputActionValue& Value);

	void JumpStarted();
	void JumpEnded();

	void Attack();

	void OnPickupAction();
	void OnDropAction();

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* PickupAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* DropAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* JoinGameMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* JoinGameAction;

	UPROPERTY()
	ASparCharacter* ControlledCharacter;
};
