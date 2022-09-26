// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BoltPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BOLT_API ABoltPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void ShowRatingScreen();

	void ShowGameOverScreen();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> RatingScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> GameOverScreenClass;

	UPROPERTY()
	UUserWidget* HUDScreen;
};
