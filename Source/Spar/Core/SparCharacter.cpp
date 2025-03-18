// Fill out your copyright notice in the Description page of Project Settings.


#include "SparCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "InteractComponent.h"
#include "PaperFlipbookComponent.h"

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
	WeaponAttachPoint->SetupAttachment(RootComponent);
	

	DoubleJumpSocket = CreateDefaultSubobject<USceneComponent>("Double Jump Socket");
	DoubleJumpSocket->SetupAttachment(RootComponent);

	DoubleJump = CreateDefaultSubobject<UPaperFlipbookComponent>("Double Jump Effect");
	DoubleJump->SetupAttachment(DoubleJumpSocket);

	InteractComponent = CreateDefaultSubobject<UInteractComponent>("Interact Component");
	// InteractComponent->SetupAtt
}

void ASparCharacter::BeginPlay()
{
	Super::BeginPlay();
	DoubleJump->Stop();
	DoubleJump->SetLooping(false);
	DoubleJump->SetVisibility(false);

	WeaponAttachPoint->SetRelativeLocation(FVector::ZeroVector);
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
	WeaponToEquip->AttachToComponent(WeaponAttachPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	EquippedWeapon = WeaponToEquip;

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

bool ASparCharacter::IsTeleporting() const
{
	return bIsTeleporting;
}

void ASparCharacter::SetTeleporting(bool bNewTeleporting)
{
	bIsTeleporting = bNewTeleporting;
}

void ASparCharacter::DropItem()
{
	if (IsValid(EquippedWeapon))
	{
		FDetachmentTransformRules DetachmentRules = FDetachmentTransformRules(
			EDetachmentRule::KeepWorld,
			EDetachmentRule::KeepWorld,
			EDetachmentRule::KeepWorld,
			true
		);
		EquippedWeapon->DetachFromActor(DetachmentRules);
		EquippedWeapon->OnWeaponDropped();
		EquippedWeapon = nullptr;
		bIsArmed = false;
	}
}

void ASparCharacter::Attack()
{
	if (IsValid(EquippedWeapon))
	{
		EquippedWeapon->Attack();
	}
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
