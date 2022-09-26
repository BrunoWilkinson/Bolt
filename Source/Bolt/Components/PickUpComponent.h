// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "../Characters/PlayerCharacter.h"
#include "PickUpComponent.generated.h"

// Declaration of the delegate that will be called when someone picks this up
// The character picking this up is the parameter sent with the notification
// change FR to F
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FROnPickUp, APlayerCharacter*, PickUpCharacter);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BOLT_API UPickUpComponent : public USphereComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickUpComponent();

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FROnPickUp OnPickUp;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Code for when something overlaps this component */
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);	
};
