// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BotCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BOLT_API ABotCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector LineTraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UParticleSystem* FireParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* DeathAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	UFUNCTION()
	void Death();

	UFUNCTION(BlueprintPure)
	bool GetHasSeenPlayer() const { return bHasSeenPlayer; }

	void SetHasSeenPlayer(bool bValue);

	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere, Category = Gameplay)
	float Damage = 20.0f;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	float LifeSpan = 5.0f;

	UAnimInstance* AnimInstance;

	bool bHasSeenPlayer;

	void DrawTraceLine();
};
