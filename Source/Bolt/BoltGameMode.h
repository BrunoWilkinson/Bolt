// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BoltGameMode.generated.h"

class UHealthComponent;

UENUM()
enum ERating
{
	A,
	B,
	C,
	D,
	F
};

UCLASS(minimalapi)
class ABoltGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABoltGameMode();

	UFUNCTION(BluePrintCallable)
	TEnumAsByte<ERating> GetRating();

	UFUNCTION(BluePrintCallable)
	float GetRawRating();

	UFUNCTION(BlueprintCallable)
	void EndGame();

	UFUNCTION(BlueprintCallable)
	void GameOver();

	UFUNCTION(BlueprintPure)
	int32 GetTotalEnemiesKilled();

	UFUNCTION(BlueprintPure)
	int32 GetTotalDestroyedObjects();

protected:
	void BeginPlay() override;

	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere, Category=Gameplay)
	float MaxRating = 90000;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	float TimeMultiplier = 3.0f;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	float DestructionMultiplier = 2.0f;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	float EnemyMultiplier = 1.0f;

	UHealthComponent* PlayerHealthComponent;

	int32 InitialTotalEnemies;

	int32 InitialTotalDestructibleObjects;

	int32 GetTotalEnemies();

	int32 GetTotalDestructibleObjects();
};



