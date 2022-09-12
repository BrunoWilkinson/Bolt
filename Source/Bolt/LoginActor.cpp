// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginActor.h"
#include "Core/PlayFabClientAPI.h"

// Sets default values
ALoginActor::ALoginActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ALoginActor::OnSuccess(const PlayFab::ClientModels::FLoginResult& Result) const
{
    UE_LOG(LogTemp, Log, TEXT("Congratulations, you made your first successful API call!"));
}

void ALoginActor::OnError(const PlayFab::FPlayFabCppError& ErrorResult) const
{
    UE_LOG(LogTemp, Error, TEXT("Something went wrong with your first API call.\nHere's some debug information:\n%s"), *ErrorResult.GenerateErrorReport());
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
        PlayFab::UPlayFabClientAPI::FLoginWithCustomIDDelegate::CreateUObject(this, &ALoginActor::OnSuccess),
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
    // 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz
    FString Alphabet = TEXT("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    FString RandomString;

    for (int32 Index = 0; Index < Alphabet.Len(); Index++)
    {
        RandomString.Append(Alphabet.Mid(FMath::RandRange(0, Alphabet.Len()), 1));
    }
   
    return RandomString;
}

