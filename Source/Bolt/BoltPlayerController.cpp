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
