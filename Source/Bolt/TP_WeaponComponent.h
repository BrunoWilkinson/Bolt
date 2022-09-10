// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TP_WeaponComponent.generated.h"

class ABoltCharacter;
class AWeapon;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOLT_API UTP_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UParticleSystem* FireParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UParticleSystem* ImpactParticles;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector LineTraceDistance;

	/** Sets default values for this component's properties */
	UTP_WeaponComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(ABoltCharacter* TargetCharacter);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

	UFUNCTION(BlueprintPure)
	float GetAmmo() const { return Ammo; }

protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
		
private:
	UPROPERTY(EditAnywhere, Category = Gameplay)
	float Damage = 20.0f;

	UPROPERTY(VisibleAnywhere, Category = Gameplay)
	float Ammo;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	float MaxAmmo = 15.0f;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	float FireRate = 0.5f;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	float ReloadTime = 2.0f;;

	/** The Character holding this weapon*/
	ABoltCharacter* Character;

	AWeapon* Weapon;

	FTimerHandle AmmoTimerHandle;

	FTimerHandle FireRateTimerHandle;

	void Reload();
};
