// Copyright Epic Games, Inc. All Rights Reserved.

#include "BoltGameMode.h"
#include "BoltCharacter.h"
#include "AICharacter.h"
#include "BoltPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ABoltGameMode::ABoltGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

TEnumAsByte<ERating> ABoltGameMode::GetRating()
{
	int32 FinalEnemyCount = InitialEnemyCount - EnemyCount();
	int32 FinalDestructionCount = InitialDestructionCount - DestructionCount();
	float Rating = TimeCount * TimeMultiplier + FinalDestructionCount * DestructionMultiplier + FinalEnemyCount * EnemyMultiplier;
	int32 RatingPercentage = (Rating / MaxRating) * 100;
	if (RatingPercentage >= 90)
	{
		return ERating::A;
	}
	if (RatingPercentage >= 80 && RatingPercentage <= 89)
	{
		return ERating::B;
	}
	if (RatingPercentage >= 70 && RatingPercentage <= 79)
	{
		return ERating::C;
	}
	if (RatingPercentage >= 60 && RatingPercentage <= 69)
	{
		return ERating::D;
	}
	return ERating::F;
}

void ABoltGameMode::EndGame()
{
	ABoltPlayerController* PlayerController = Cast<ABoltPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController != nullptr)
	{
		PlayerController->ShowRatingScreen();
		PlayerController->Pause();
		PlayerController->bShowMouseCursor = true;
	}
}

void ABoltGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitialEnemyCount = EnemyCount();
	InitialDestructionCount = DestructionCount();
}

void ABoltGameMode::Tick(float DeltaTime)
{
	TimeCount += GetWorld()->GetTimeSeconds();
}

int32 ABoltGameMode::EnemyCount()
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAICharacter::StaticClass(), Enemies);
	return Enemies.Num();
}

int32 ABoltGameMode::DestructionCount()
{
	TArray<AActor*> DestroyedObjects;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Destructible"), DestroyedObjects);
	return DestroyedObjects.Num();
}
