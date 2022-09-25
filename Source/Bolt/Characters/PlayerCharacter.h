// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class AWeapon;
class USpellComponent;

// Declaration of the delegate that will be called when the Primary Action is triggered
// It is declared as dynamic so it can be accessed also in Blueprints
// change the FR to F
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FROnUseItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FROnUseSpell);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FROnReload);

UCLASS(config = Game)
class BOLT_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();

public:
	APlayerCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float TurnRateGamepad;

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FROnUseItem OnUseItem;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FROnUseSpell OnUseSpell;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FROnReload OnUseReload;

	UFUNCTION(BlueprintPure)
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	UFUNCTION(BlueprintPure)
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION(BlueprintPure)
	USpellComponent* GetSpellComponent() const { return SpellComponent; }

	UFUNCTION(BlueprintPure)
	AWeapon* GetWeapon() const { return Weapon; }

protected:
	/** Fires a projectile. */
	void OnPrimaryAction();

	void OnSpellAction();

	void OnReload();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false; Location = FVector::ZeroVector; }
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};

	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);

	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);

	TouchData TouchItem;

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/*
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

private:
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	USpellComponent* SpellComponent;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeapon> WeaponClass;

	AWeapon* Weapon;
};
