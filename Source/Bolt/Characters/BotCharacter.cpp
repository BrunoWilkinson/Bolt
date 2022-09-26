// Fill out your copyright notice in the Description page of Project Settings.

#include "BotCharacter.h"
#include "../Components/HealthComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void ABotCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (HealthComponent != nullptr)
	{
		HealthComponent->OnDeath.AddDynamic(this, &ABotCharacter::Death);
	}
	AnimInstance = GetMesh()->GetAnimInstance();
}

void ABotCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (HealthComponent != nullptr)
	{
		HealthComponent->OnDeath.RemoveDynamic(this, &ABotCharacter::Death);
	}
}

void ABotCharacter::Death()
{
	SetActorEnableCollision(false);
	DetachFromControllerPendingDestroy();
	if (AnimInstance != nullptr && DeathAnimation != nullptr)
	{
		AnimInstance->Montage_Play(DeathAnimation, 1.f);
	}
	SetLifeSpan(LifeSpan);
}

void ABotCharacter::SetHasSeenPlayer(bool bValue)
{
	bHasSeenPlayer = bValue;
}

void ABotCharacter::Shoot()
{
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (FireParticles != nullptr)
	{
		UGameplayStatics::SpawnEmitterAttached(FireParticles, GetMesh(), TEXT("Muzzle_01"));
	}

	if (AnimInstance != nullptr && FireAnimation != nullptr)
	{
		AnimInstance->Montage_Play(FireAnimation, 1.f);
	}

	DrawTraceLine();
}

void ABotCharacter::DrawTraceLine()
{
	FVector Start = GetActorLocation() + GetActorRotation().RotateVector(MuzzleOffset);
	FVector End = Start + GetActorRotation().RotateVector(LineTraceDistance);

	FHitResult HitResult;
	bool HasHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel2);

	if (HasHit)
	{
		if (ImpactParticles != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, HitResult.ImpactPoint, HitResult.Location.Rotation());
		}
		APlayerCharacter* Player = Cast<APlayerCharacter>(HitResult.GetActor());
		if (Player != nullptr)
		{
			UHealthComponent* PlayerHealthComponent = Player->GetHealthComponent();
			if (PlayerHealthComponent != nullptr)
			{
				PlayerHealthComponent->ApplyDamage(Damage);
			}
		}
	}
}
