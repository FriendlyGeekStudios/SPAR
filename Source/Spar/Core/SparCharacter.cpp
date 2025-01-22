// Fill out your copyright notice in the Description page of Project Settings.


#include "SparCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "PaperFlipbookComponent.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Spar/Weapons/WeaponBase.h"


// Sets default values
ASparCharacter::ASparCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>("Weapon Attach Point");

	DoubleJumpSocket = CreateDefaultSubobject<USceneComponent>("Double Jump Socket");
	DoubleJumpSocket->SetupAttachment(RootComponent);

	DoubleJump = CreateDefaultSubobject<UPaperFlipbookComponent>("Double Jump Effect");
	DoubleJump->SetupAttachment(DoubleJumpSocket);
}

void ASparCharacter::BeginPlay()
{
	Super::BeginPlay();
	DoubleJump->Stop();
	DoubleJump->SetLooping(false);
	DoubleJump->SetVisibility(false);
}

void ASparCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ASparCharacter::HasWeapon() const
{
	return bIsArmed;
}

void ASparCharacter::EquipWeapon(AWeaponBase* WeaponToEquip)
{
	WeaponToEquip->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

	bIsArmed = true;
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
			Controller->SetControlRotation(FRotator(CurrentRotation.Pitch, 180.0f, CurrentRotation.Roll));
		}
	}
	else if (MoveDirection > 0.0f)
	{
		// Face Right
		if (CurrentRotation.Yaw != 0.0f)
		{
			Controller->SetControlRotation(FRotator(CurrentRotation.Pitch, 0.0f, CurrentRotation.Roll));
		}
	}
}

void ASparCharacter::JumpStarted()
{
	Jump();
}

void ASparCharacter::JumpEnded()
{
	StopJumping();
}

void ASparCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
	if (JumpCurrentCount > 1)
	{
		EnableDoubleJumpEffect();
		const float FlipbookLength = DoubleJump->GetFlipbookLength();
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			[&]() -> void
			{
				DisableDoubleJumpEffect();
				TimerHandle.Invalidate();
			},
			FlipbookLength,
			false
		);
	}
}

void ASparCharacter::EnableDoubleJumpEffect()
{
	FDetachmentTransformRules DetachmentRules = FDetachmentTransformRules(
		EDetachmentRule::KeepWorld,
		EDetachmentRule::KeepWorld,
		EDetachmentRule::KeepWorld,
		true
	);
	DoubleJump->DetachFromComponent(DetachmentRules);
	DoubleJump->SetVisibility(true);
	DoubleJump->PlayFromStart();
}

void ASparCharacter::DisableDoubleJumpEffect()
{
	DoubleJump->Stop();
	DoubleJump->SetVisibility(false);
	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(
		EAttachmentRule::KeepRelative,
		EAttachmentRule::KeepRelative,
		EAttachmentRule::KeepRelative,
		false
	);
	const bool AttachementResult = DoubleJump->AttachToComponent(DoubleJumpSocket, AttachmentRules);
	if (AttachementResult)
	{
		DoubleJump->SetRelativeLocation(FVector::ZeroVector);
	}
}
