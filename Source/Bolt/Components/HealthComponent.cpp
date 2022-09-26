// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

bool UHealthComponent::IsDead() const
{
	if (Health <= 0)
	{
		return true;
	}
	return false;
}

void UHealthComponent::ApplyDamage(float Value)
{
	Health -= FMath::Min(Health, Value);
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
}
