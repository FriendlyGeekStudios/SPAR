﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter.h"

#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Spar/Core/SparCharacter.h"

// Sets default values
ATeleporter::ATeleporter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	SetRootComponent(SceneRoot);

	TeleporterFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Teleporter Sprite"));
	TeleporterFlipbook->SetupAttachment(SceneRoot);


	RightEntranceCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Entrance"));
	RightEntranceCollider->SetupAttachment(SceneRoot);
	LeftEntranceCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Entrance"));
	LeftEntranceCollider->SetupAttachment(SceneRoot);

	RightOutput = CreateDefaultSubobject<USceneComponent>(TEXT("Right Spawn Point"));
	RightOutput->SetupAttachment(RightEntranceCollider);
	LeftOutput = CreateDefaultSubobject<USceneComponent>(TEXT("Left Spawn Point"));
	LeftOutput->SetupAttachment(LeftEntranceCollider);
}

void ATeleporter::OnPlayerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != LastTeleportedActor)
	{
		ASparCharacter* Character = Cast<ASparCharacter>(OtherActor);
		if (Character)
		{
			Character->SetTeleporting(false);
			DestinationTeleporter->ClearLastTeleportedActor();
		}
	}
}

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();

	check(DestinationTeleporter != nullptr);

	RightEntranceCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATeleporter::OnPlayerEnterRight);
	LeftEntranceCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATeleporter::OnPlayerEnterLeft);

	RightEntranceCollider->OnComponentEndOverlap.AddUniqueDynamic(this, &ATeleporter::OnPlayerExit);
	LeftEntranceCollider->OnComponentEndOverlap.AddUniqueDynamic(this, &ATeleporter::OnPlayerExit);
}

void ATeleporter::OnPlayerEnterRight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASparCharacter* Character = Cast<ASparCharacter>(OtherActor);
	if (Character && !Character->IsTeleporting())
	{
		Character->SetTeleporting(true);
		TeleportPlayerTo(OtherActor, DestinationTeleporter->LeftOutput->GetComponentLocation());
	}
}

void ATeleporter::OnPlayerEnterLeft(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASparCharacter* Character = Cast<ASparCharacter>(OtherActor);
	if (Character && !Character->IsTeleporting())
	{
		Character->SetTeleporting(true);
		TeleportPlayerTo(OtherActor, DestinationTeleporter->RightOutput->GetComponentLocation());
	}
}

void ATeleporter::ClearLastTeleportedActor()
{
	LastTeleportedActor = nullptr;
}

// Called every frame
void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATeleporter::TeleportPlayerTo(AActor* InActor, const FVector& Destination)
{
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, "Teleporting Player");
	LastTeleportedActor = InActor;
	InActor->SetActorLocation(Destination);
}
