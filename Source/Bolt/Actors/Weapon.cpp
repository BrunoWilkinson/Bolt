// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "../Components/PickUpComponent.h"
#include "../Components/WeaponComponent.h"

// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	PickUpComponent = CreateDefaultSubobject<UPickUpComponent>(TEXT("PickUp Component"));
	PickUpComponent->SetupAttachment(RootComponent);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(PickUpComponent);

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon Component"));
}
