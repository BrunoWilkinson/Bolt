// Fill out your copyright notice in the Description page of Project Settings.


#include "DrongoAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void ADrongoAIController::BeginPlay()
{
	Super::BeginPlay();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (AIBehavior != nullptr && PlayerPawn != nullptr)
	{
		RunBehaviorTree(AIBehavior);
	}
}

void ADrongoAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
