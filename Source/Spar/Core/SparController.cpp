// Fill out your copyright notice in the Description page of Project Settings.


#include "SparController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SparCharacter.h"
#include "SparGameMode.h"

void ASparController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASparController::Move);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASparController::JumpStarted);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASparController::JumpEnded);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Canceled, this, &ASparController::JumpEnded);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ASparController::Attack);
	}
}

void ASparController::SetupInactiveStateInputComponent(UInputComponent* InComponent)
{
	Super::SetupInactiveStateInputComponent(InComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(JoinGameAction, ETriggerEvent::Triggered, this, &ASparController::OnJoinGameTriggered);
	}
}

void ASparController::BeginPlay()
{
	Super::BeginPlay();
}

void ASparController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ControlledCharacter = Cast<ASparCharacter>(InPawn);

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(InputSubsystem))
	{
		InputSubsystem->AddMappingContext(GameplayMappingContext, 0);
	}
}

void ASparController::Move(const FInputActionValue& Value)
{
	if (IsValid(ControlledCharacter))
	{
		ControlledCharacter->Move(Value);
	}
}

void ASparController::JumpStarted()
{
	if (IsValid(ControlledCharacter))
	{
		ControlledCharacter->JumpStarted();
	}
}

void ASparController::JumpEnded()
{
	if (IsValid(ControlledCharacter))
	{
		ControlledCharacter->JumpEnded();
	}
}

void ASparController::Attack()
{
	if (IsValid(ControlledCharacter))
	{
		ControlledCharacter->Attack();
	}
}


void ASparController::OnJoinGameTriggered()
{
	// Tell the GameMode to spawn me a characters
	ASparGameMode* GameMode = Cast<ASparGameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameMode))
	{
		GameMode->SpawnNewPlayer(this);
	}
}

void ASparController::BeginInactiveState()
{
	Super::BeginInactiveState();
	// Map the join game  mapping context
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(InputSubsystem))
	{
		InputSubsystem->AddMappingContext(JoinGameMappingContext, 0);
	}
}

void ASparController::EndInactiveState()
{
	Super::EndInactiveState();
	// Unmap the join game mapping context
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(InputSubsystem))
	{
		InputSubsystem->RemoveMappingContext(JoinGameMappingContext);
	}
}
