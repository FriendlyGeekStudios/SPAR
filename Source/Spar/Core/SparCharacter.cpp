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

	ExtraJumpEffect = CreateDefaultSubobject<UPaperFlipbookComponent>("Extra Jump Effect");
	ExtraJumpEffect->SetupAttachment(RootComponent);
}

void ASparCharacter::BeginPlay()
{
	Super::BeginPlay();
	ExtraJumpEffect->Stop();
	ExtraJumpEffect->SetLooping(false);
	ExtraJumpEffect->SetVisibility(false);
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
	if (JumpCurrentCount <= 1)
	{
		return;
	}

	UPaperFlipbookComponent* ExtraJumpDuplicate = EnableExtraJumpEffect();
	const float FlipbookLength = ExtraJumpDuplicate->GetFlipbookLength();
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		[&, Duplicate=ExtraJumpDuplicate]() -> void
		{
			DisableExtraJumpEffect(Duplicate);
			TimerHandle.Invalidate();
		},
		FlipbookLength,
		false
	);
}

UPaperFlipbookComponent* ASparCharacter::EnableExtraJumpEffect()
{
	UPaperFlipbookComponent* ExtraJumpDuplicate = DuplicateObject<UPaperFlipbookComponent>(ExtraJumpEffect, ExtraJumpEffect->GetOuter());
	if (IsValid(ExtraJumpDuplicate))
	{
		ExtraJumpDuplicate->RegisterComponent();
		const FDetachmentTransformRules DetachmentRules = FDetachmentTransformRules(
			EDetachmentRule::KeepWorld,
			EDetachmentRule::KeepWorld,
			EDetachmentRule::KeepWorld,
			true
		);
		ExtraJumpDuplicate->DetachFromComponent(DetachmentRules);
		ExtraJumpDuplicate->SetVisibility(true);
		ExtraJumpDuplicate->PlayFromStart();
	}
	return ExtraJumpDuplicate;
}

void ASparCharacter::DisableExtraJumpEffect(UPaperFlipbookComponent* ExtraJumpDuplicate)
{
	if (IsValid(ExtraJumpDuplicate))
	{
		ExtraJumpDuplicate->Stop();
		ExtraJumpDuplicate->SetVisibility(false);
		ExtraJumpDuplicate->DestroyComponent();
	}
}
