// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOLT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintPure)
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnDeath OnDeath;

	void ApplyDamage(float Value);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Values)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = Values)
	float Health;
};
