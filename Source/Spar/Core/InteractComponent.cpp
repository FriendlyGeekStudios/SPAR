// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"

#include "Interactable.h"
#include "Components/SphereComponent.h"


// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	PickupRange = CreateDefaultSubobject<USphereComponent>("Pickup Range");
}

void UInteractComponent::Interact()
{
	if (InteractTarget != nullptr) // if(InteractTarget)
	{
		// IInteractable::Execute_Interact(InteractTarget);
		InteractTarget->Interact();
	}
}

void UInteractComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                        const FHitResult& SweepResult)
{
	if (IInteractable* OverlapTarget = Cast<IInteractable>(OtherActor))
	{
		InteractTarget = OverlapTarget;
	}
}


void UInteractComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IInteractable* OverlapTarget = Cast<IInteractable>(OtherActor))
	{
		InteractTarget = nullptr;
	}
}

// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	PickupRange->OnComponentBeginOverlap.AddDynamic(this, &UInteractComponent::OnOverlapBegin);
	PickupRange->OnComponentEndOverlap.AddDynamic(this, &UInteractComponent::OnOverlapEnd);
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
