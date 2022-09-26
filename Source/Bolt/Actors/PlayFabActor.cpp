// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayFabActor.h"
#include "Core/PlayFabClientAPI.h"

// Called when the game starts or when spawned
void APlayFabActor::BeginPlay()
{
	Super::BeginPlay();

    GetMutableDefault<UPlayFabRuntimeSettings>()->TitleId = TEXT("3DC66");

    clientAPI = IPlayFabModuleInterface::Get().GetClientAPI();

    PlayFab::ClientModels::FLoginWithCustomIDRequest request;
    request.CustomId = RandomString();
    request.CreateAccount = true;

    UE_LOG(LogTemp, Log, TEXT("PlayFab CustomID: %s"), *request.CustomId);

    clientAPI->LoginWithCustomID(request,
        PlayFab::UPlayFabClientAPI::FLoginWithCustomIDDelegate::CreateUObject(this, &APlayFabActor::OnLoginSuccess),
        PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &APlayFabActor::OnError)
    );
}

void APlayFabActor::OnLoginSuccess(const PlayFab::ClientModels::FLoginResult& Result) const
{
    UE_LOG(LogTemp, Log, TEXT("PlayFab: Login with success"));
}

void APlayFabActor::OnSubmitScoreSuccess(const PlayFab::ClientModels::FUpdatePlayerStatisticsResult& Result) const
{
    UE_LOG(LogTemp, Log, TEXT("PlayFab: Submit Score with success"));
}

void APlayFabActor::OnError(const PlayFab::FPlayFabCppError& ErrorResult) const
{
    UE_LOG(LogTemp, Error, TEXT("PlayFab: Something went wrong. %s"), *ErrorResult.GenerateErrorReport());
}

void APlayFabActor::SubmitScore(float Score)
{
    PlayFab::ClientModels::FUpdatePlayerStatisticsRequest request;
    PlayFab::ClientModels::FStatisticUpdate PlayerValue;
    PlayerValue.StatisticName = TEXT("Rating");
    PlayerValue.Value = Score;
    request.Statistics.Add(PlayerValue);

    clientAPI->UpdatePlayerStatistics(request,
        PlayFab::UPlayFabClientAPI::FUpdatePlayerStatisticsDelegate::CreateUObject(this, &APlayFabActor::OnSubmitScoreSuccess),
        PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &APlayFabActor::OnError)
    );
}

FString APlayFabActor::RandomString()
{
    FString Alphabet = TEXT("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    FString RandomString;

    for (int32 Index = 0; Index < Alphabet.Len(); Index++)
    {
        RandomString.Append(Alphabet.Mid(FMath::RandRange(0, Alphabet.Len()), 1));
    }

    return RandomString;
}
