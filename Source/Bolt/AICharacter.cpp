// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "HealthComponent.h"
#include "BoltCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	if (HealthComponent != nullptr)
	{
		HealthComponent->OnDeath.AddDynamic(this, &AAICharacter::Death);
	}
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAICharacter::SetHasSeenPlayer(bool bValue)
{
	bHasSeenPlayer = bValue;
}

void AAICharacter::Shoot()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance != nullptr && FireAnimation != nullptr)
	{
		AnimInstance->Montage_Play(FireAnimation, 1.f);
	}

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	FVector Start = GetActorLocation() + GetActorRotation().RotateVector(MuzzleOffset);
	FVector End = Start + GetActorRotation().RotateVector(LineTraceDistance);

	DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, false, 3.0f, 0, 2.0f);

	FHitResult HitResult;
	bool HasHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel2);

	if (HasHit)
	{
		ABoltCharacter* Player = Cast<ABoltCharacter>(HitResult.GetActor());
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

void AAICharacter::Death()
{
	SetActorEnableCollision(false);
	DetachFromControllerPendingDestroy();
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance != nullptr && DeathAnimation != nullptr)
	{
		AnimInstance->Montage_Play(DeathAnimation, 1.f);
	}
	SetLifeSpan(LifeSpan);
}

void AAICharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (HealthComponent != nullptr)
	{
		HealthComponent->OnDeath.RemoveDynamic(this, &AAICharacter::Death);
	}
}
