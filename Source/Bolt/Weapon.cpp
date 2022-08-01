// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "TP_PickUpComponent.h"
#include "TP_WeaponComponent.h"

// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	PickUpComponent = CreateDefaultSubobject<UTP_PickUpComponent>(TEXT("PickUp Component"));
	PickUpComponent->SetupAttachment(RootComponent);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(PickUpComponent);

	WeaponComponent = CreateDefaultSubobject<UTP_WeaponComponent>(TEXT("Weapon Component"));
}
