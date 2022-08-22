// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BoltGameMode.generated.h"

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

	TEnumAsByte<ERating> GetRating();

protected:
	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category=Gameplay)
	float MaxRating = 90000;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	float TimeMultiplier = 3.0f;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	float DestructionMultiplier = 2.0f;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	float EnemyMultiplier = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = Information)
	int32 InitialEnemyCount;

	UPROPERTY(VisibleAnywhere, Category = Information)
	int32 InitialDestructionCount;

	UPROPERTY(VisibleAnywhere, Category = Information)
	float TimeCount;

	int32 EnemyCount();

	int32 DestructionCount();
};



