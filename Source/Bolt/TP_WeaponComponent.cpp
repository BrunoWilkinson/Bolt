// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "BoltCharacter.h"
#include "AICharacter.h"
#include "HealthComponent.h"
#include "Weapon.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
	LineTraceDistance = FVector(500.0f, 0.0f, 10.0f);
	Ammo = MaxAmmo;
	Weapon = Cast<AWeapon>(GetOwner());
}


void UTP_WeaponComponent::Fire()
{	
	if (GetWorld()->GetTimerManager().IsTimerActive(FireRateTimerHandle) || 
		GetWorld()->GetTimerManager().IsTimerActive(AmmoTimerHandle))
	{
		return;
	}

	if (Ammo <= 0)
	{
		Reload();
		return;
	}

	if(Character == nullptr || Character->GetController() == nullptr)
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

	if (FireParticles != nullptr && Weapon != nullptr)
	{
		UGameplayStatics::SpawnEmitterAttached(FireParticles, Weapon->GetMeshComponent(), TEXT("Muzzle"));
	}

	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();

	FVector Start = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	FVector End = Start + SpawnRotation.RotateVector(LineTraceDistance);

	FHitResult HitResult;
	bool HasHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel3);

	if (HasHit)
	{
		if (ImpactParticles != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, HitResult.ImpactPoint, HitResult.Location.Rotation());
		}
		AAICharacter* AICharacter = Cast<AAICharacter>(HitResult.GetActor());
		if (AICharacter != nullptr)
		{
			UHealthComponent* HealthComponent = AICharacter->GetHealthComponent();
			if (HealthComponent != nullptr)
			{
				HealthComponent->ApplyDamage(Damage);
			}
		}
	}

	FTimerDelegate FireRateTimerDelegate;
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, FireRateTimerDelegate, FireRate, false);
	Ammo--;
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(Character != nullptr)
	{
		// Unregister from the OnUseItem Event
		Character->OnUseItem.RemoveDynamic(this, &UTP_WeaponComponent::Fire);
		Character->OnUseReload.RemoveDynamic(this, &UTP_WeaponComponent::Reload);
	}
}

void UTP_WeaponComponent::Reloading()
{
	Ammo = MaxAmmo;
}

void UTP_WeaponComponent::Reload()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(AmmoTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(AmmoTimerHandle, this, &UTP_WeaponComponent::Reloading, ReloadTime, false);
	}
}

void UTP_WeaponComponent::AttachWeapon(ABoltCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	if(Character != nullptr)
	{
		// Attach the weapon to the First Person Character
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		GetOwner()->AttachToComponent(Character->GetMesh1P(),AttachmentRules, FName(TEXT("GripPoint")));

		// Register so that Fire is called every time the character tries to use the item being held
		Character->OnUseItem.AddDynamic(this, &UTP_WeaponComponent::Fire);
		Character->OnUseReload.AddDynamic(this, &UTP_WeaponComponent::Reload);
	}
}

