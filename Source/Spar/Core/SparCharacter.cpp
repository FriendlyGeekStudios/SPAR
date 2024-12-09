// Fill out your copyright notice in the Description page of Project Settings.


#include "SparCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


// Sets default values
ASparCharacter::ASparCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ASparCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (IsValid(PlayerController))
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (IsValid(InputSubsystem))
		{
			InputSubsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ASparCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASparCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent =  Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASparCharacter::Move);
	}
}

void ASparCharacter::Move(const FInputActionValue& Value)
{
	float MoveValue = Value.Get<float>();
	UpdateDirection(MoveValue);
	FVector Direction = FVector(1, 0, 0);
	AddMovementInput(Direction, MoveValue);
}

void ASparCharacter::UpdateDirection(float MoveDirection)
{
	FRotator CurrentRotation = Controller->GetControlRotation();
	if (MoveDirection < 0.0f)
	{
		// Face Left
		if (CurrentRotation.Yaw != 180.0f)
		{
			// Update rotation
			Controller->SetControlRotation(FRotator(CurrentRotation.Pitch, 180.0f,CurrentRotation.Roll));
		}
	} else if ( MoveDirection > 0.0f )
	{
		// Face Right
		if (CurrentRotation.Yaw != 0.0f)
		{
			Controller->SetControlRotation(FRotator(CurrentRotation.Pitch, 0.0f,CurrentRotation.Roll));
		}
	}
}
