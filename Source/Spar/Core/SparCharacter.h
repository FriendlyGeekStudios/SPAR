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

UCLASS()
class SPAR_API ASparCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ASparCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool HasWeapon() const;

	void EquipWeapon(AWeaponBase* WeaponToEquip);

	void Move(const FInputActionValue& Value);
	void JumpStarted();
	void JumpEnded();

	void Attack();

private:
	void UpdateDirection(float MoveDirection);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> WeaponAttachPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<AWeaponBase> EquippedWeapon;
private:
	bool bIsArmed = false;
};
