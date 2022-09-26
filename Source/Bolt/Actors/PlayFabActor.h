// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayFab.h"
#include "Core/PlayFabError.h"
#include "Core/PlayFabClientDataModels.h"
#include "PlayFabActor.generated.h"

UCLASS()
class BOLT_API APlayFabActor : public AActor
{
	GENERATED_BODY()
	
public:	
	void OnLoginSuccess(const PlayFab::ClientModels::FLoginResult& Result) const;
	void OnSubmitScoreSuccess(const PlayFab::ClientModels::FUpdatePlayerStatisticsResult& Result) const;
	void OnError(const PlayFab::FPlayFabCppError& ErrorResult) const;

	UFUNCTION(BluePrintCallable)
	void SubmitScore(float Score);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	PlayFabClientPtr clientAPI = nullptr;
	FString RandomString();
};
