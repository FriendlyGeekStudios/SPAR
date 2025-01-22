// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "InputActionValue.h"
#include "SparCharacter.generated.h"

class AWeaponBase;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class UPaperFlipbookComponent;

UCLASS()
class SPAR_API ASparCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ASparCharacter();

	virtual void OnJumped_Implementation() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool HasWeapon() const;

	void EquipWeapon(AWeaponBase* WeaponToEquip);

	void Move(const FInputActionValue& Value);
	void JumpStarted();
	void JumpEnded();

	void Attack();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> WeaponAttachPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPaperFlipbookComponent> ExtraJumpEffect;

	TObjectPtr<AWeaponBase> EquippedWeapon = nullptr;

private:
	bool bIsArmed = false;
	UPaperFlipbookComponent* EnableExtraJumpEffect();
	void DisableExtraJumpEffect(UPaperFlipbookComponent* ExtraJumpDuplicate);
	void UpdateDirection(float MoveDirection);
};
