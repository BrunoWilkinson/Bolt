// Copyright Epic Games, Inc. All Rights Reserved.

#include "BoltGameMode.h"
#include "BoltCharacter.h"
#include "AICharacter.h"
#include "HealthComponent.h"
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

void ABoltGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitialTotalEnemies = GetTotalEnemies();
	InitialTotalDestructibleObjects = GetTotalDestructibleObjects();

	ABoltCharacter* PlayerCharacter = Cast<ABoltCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (PlayerCharacter != nullptr)
	{
		PlayerHealthComponent = PlayerCharacter->GetHealthComponent();
		PlayerHealthComponent->OnDeath.AddDynamic(this, &ABoltGameMode::GameOver);
	}
}

TEnumAsByte<ERating> ABoltGameMode::GetRating()
{
	float TimeScore = 50 * 100 / GetWorld()->GetTimeSeconds();
	float Rating = TimeScore * TimeMultiplier + GetTotalDestroyedObjects() * DestructionMultiplier + GetTotalEnemiesKilled() * EnemyMultiplier;
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
	ABoltPlayerController* PlayerController = Cast<ABoltPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController != nullptr)
	{
		PlayerController->ShowRatingScreen();
		PlayerController->Pause();
		PlayerController->bShowMouseCursor = true;
	}
}

void ABoltGameMode::GameOver()
{
	ABoltPlayerController* PlayerController = Cast<ABoltPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController != nullptr)
	{
		PlayerController->ShowGameOverScreen();
		PlayerController->Pause();
		PlayerController->bShowMouseCursor = true;
	}
}

int32 ABoltGameMode::GetTotalEnemiesKilled()
{
	return InitialTotalEnemies - GetTotalEnemies();
}

int32 ABoltGameMode::GetTotalDestroyedObjects()
{
	return InitialTotalDestructibleObjects - GetTotalDestructibleObjects();
}

int32 ABoltGameMode::GetTotalEnemies()
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAICharacter::StaticClass(), Enemies);
	return Enemies.Num();
}

int32 ABoltGameMode::GetTotalDestructibleObjects()
{
	TArray<AActor*> DestroyedObjects;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Destructible"), DestroyedObjects);
	return DestroyedObjects.Num();
}

void ABoltGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	PlayerHealthComponent->OnDeath.RemoveDynamic(this, &ABoltGameMode::GameOver);
}
