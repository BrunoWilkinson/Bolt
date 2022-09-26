// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UPickUpComponent;
class UWeaponComponent;

UCLASS()
class BOLT_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();


public:
	UFUNCTION(BlueprintPure)
	UPickUpComponent* GetPickUpComponent() const { return PickUpComponent; };

	UFUNCTION(BlueprintPure)
	UWeaponComponent* GetWeaponComponent() const { return WeaponComponent; };

	UFUNCTION(BlueprintPure)
	USkeletalMeshComponent* GetMeshComponent() const { return MeshComponent; };

private:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UPickUpComponent* PickUpComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USkeletalMeshComponent* MeshComponent;
};
