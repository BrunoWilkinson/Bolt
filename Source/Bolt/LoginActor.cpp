// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginActor.h"
#include "Core/PlayFabClientAPI.h"

// Sets default values
ALoginActor::ALoginActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ALoginActor::OnLoginSuccess(const PlayFab::ClientModels::FLoginResult& Result) const
{
    UE_LOG(LogTemp, Log, TEXT("PlayFab: Login with success"));
}

void ALoginActor::OnError(const PlayFab::FPlayFabCppError& ErrorResult) const
{
    UE_LOG(LogTemp, Error, TEXT("PlayFab: Something went wrong. %s"), *ErrorResult.GenerateErrorReport());
}

void ALoginActor::OnSubmitScoreSuccess(const PlayFab::ClientModels::FUpdatePlayerStatisticsResult& Result) const
{
    UE_LOG(LogTemp, Log, TEXT("PlayFab: Submit Score with success"));
}

void ALoginActor::SendRating(int64 Value)
{
    PlayFab::ClientModels::FUpdatePlayerStatisticsRequest request;
    PlayFab::ClientModels::FStatisticUpdate PlayerValue;
    PlayerValue.StatisticName = TEXT("Rating");
    PlayerValue.Value = Value;
    request.Statistics.Add(PlayerValue);

    clientAPI->UpdatePlayerStatistics(request, 
        PlayFab::UPlayFabClientAPI::FUpdatePlayerStatisticsDelegate::CreateUObject(this, &ALoginActor::OnSubmitScoreSuccess),
        PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &ALoginActor::OnError)
    );
}

// Called when the game starts or when spawned
void ALoginActor::BeginPlay()
{
	Super::BeginPlay();

    GetMutableDefault<UPlayFabRuntimeSettings>()->TitleId = TEXT("3DC66");

    clientAPI = IPlayFabModuleInterface::Get().GetClientAPI();

    PlayFab::ClientModels::FLoginWithCustomIDRequest request;
    request.CustomId = RandomString();
    request.CreateAccount = true;

    UE_LOG(LogTemp, Log, TEXT("PlayFab CustomID: %s"), *request.CustomId);

    clientAPI->LoginWithCustomID(request,
        PlayFab::UPlayFabClientAPI::FLoginWithCustomIDDelegate::CreateUObject(this, &ALoginActor::OnLoginSuccess),
        PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &ALoginActor::OnError)
    );
}

// Called every frame
void ALoginActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString ALoginActor::RandomString()
{
    FString Alphabet = TEXT("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    FString RandomString;

    for (int32 Index = 0; Index < Alphabet.Len(); Index++)
    {
        RandomString.Append(Alphabet.Mid(FMath::RandRange(0, Alphabet.Len()), 1));
    }
   
    return RandomString;
}

