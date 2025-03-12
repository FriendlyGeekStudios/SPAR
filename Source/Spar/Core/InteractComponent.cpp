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
		AActor* Instigator = GetOwner();
		IInteractable::Execute_Interact(InteractTarget, Instigator);
		// InteractTarget->Interact(Instigator);
	}
}

void UInteractComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                        const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UInteractable>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Overlap target is an interactable"));
		InteractTarget = OtherActor;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap target is NOT interactable"));
		UE_LOG(LogTemp, Warning, TEXT("Overlap target is not an interactable"));
	}
}


void UInteractComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IInteractable* OverlapTarget = Cast<IInteractable>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Marking Target as nullptr"));
		InteractTarget = nullptr;
	}
}

// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	PickupRange->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	PickupRange->OnComponentBeginOverlap.AddDynamic(this, &UInteractComponent::OnOverlapBegin);
	PickupRange->OnComponentEndOverlap.AddDynamic(this, &UInteractComponent::OnOverlapEnd);
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
