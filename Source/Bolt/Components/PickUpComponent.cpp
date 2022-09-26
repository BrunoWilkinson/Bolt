// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpComponent.h"

// Sets default values for this component's properties
UPickUpComponent::UPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UPickUpComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UPickUpComponent::OnSphereBeginOverlap);
}

void UPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);
	if (Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
