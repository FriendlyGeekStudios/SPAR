// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugSparCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ADebugSparCharacter::ADebugSparCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
}

void ADebugSparCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADebugSparCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
