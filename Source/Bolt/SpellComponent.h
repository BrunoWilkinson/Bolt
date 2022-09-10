// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellComponent.generated.h"

class ABoltCharacter;
class AFieldSystemActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOLT_API USpellComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UParticleSystem* FireParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UParticleSystem* ImpactParticles;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector LineTraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TSubclassOf<AFieldSystemActor> FieldSystemActorClass;

	/** Sets default values for this component's properties */
	USpellComponent();

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

	UFUNCTION(BlueprintPure)
	FTimerHandle GetCooldownTimerHandle() const { return CooldownTimerHandle; }

protected:
	virtual void BeginPlay();
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere, Category = Gameplay)
	float Cooldown = 3.0f;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	float SpanLifeAfterImpact = 5.0f;

	/** The Character holding this weapon*/
	ABoltCharacter* Character;

	FTimerHandle CooldownTimerHandle;
};
