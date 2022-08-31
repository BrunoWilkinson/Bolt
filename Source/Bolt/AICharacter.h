// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

class UHealthComponent;

UCLASS()
class BOLT_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector LineTraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* DeathAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	UFUNCTION(BlueprintPure)
	UHealthComponent* GetHealthComponent() const { return HealthComponent; }

	UFUNCTION(BlueprintPure)
	bool GetHasSeenPlayer() const { return bHasSeenPlayer; }

	void SetHasSeenPlayer(bool bValue);

	void Shoot();

	UFUNCTION()
	void Death();

private:
	bool bHasSeenPlayer;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	float Damage = 20.0f;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	float LifeSpan = 5.0f;
};
