// Fill out your copyright notice in the Description page of Project Settings.


#include "BoltPlayerController.h"
#include "Blueprint/UserWidget.h"

void ABoltPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDScreen = CreateWidget(this, HUDScreenClass);
	if (HUDScreen != nullptr)
	{
		HUDScreen->AddToViewport();
	}
}

void ABoltPlayerController::ShowRatingScreen()
{
	UUserWidget* RatingScreen = CreateWidget(this, RatingScreenClass);
	if (RatingScreen != nullptr)
	{
		RatingScreen->AddToViewport();
	}
}

void ABoltPlayerController::ShowGameOverScreen()
{
	UUserWidget* GameOverScreen = CreateWidget(this, GameOverScreenClass);
	if (GameOverScreen != nullptr)
	{
		GameOverScreen->AddToViewport();
	}
}
