// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "../HealthComponent.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}
