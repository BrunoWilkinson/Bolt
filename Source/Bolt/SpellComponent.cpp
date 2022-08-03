// Fill out your copyright notice in the Description page of Project Settings.

#include "SpellComponent.h"
#include "BoltCharacter.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpellComponent::USpellComponent()
{
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
	LineTraceDistance = FVector(500.0f, 0.0f, 10.0f);
	Character = Cast<ABoltCharacter>(GetOwner());
}

void USpellComponent::BeginPlay()
{
	if (Character != nullptr)
	{
		Character->OnUseSpell.AddDynamic(this, &USpellComponent::Fire);
	}
}

void USpellComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}

	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();

	FVector Start = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	FVector End = Start + SpawnRotation.RotateVector(LineTraceDistance);

	DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 3.0f, 0, 2.0f);

	FHitResult HitResult;
	bool HasHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel2);

	if (HasHit)
	{
		// Apply chaos destructions
	}
}

void USpellComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character != nullptr)
	{
		// Unregister from the OnUseItem Event
		Character->OnUseSpell.RemoveDynamic(this, &USpellComponent::Fire);
	}
}