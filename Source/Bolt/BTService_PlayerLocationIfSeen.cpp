// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (Player != nullptr && AIController != nullptr && BlackboardComponent != nullptr)
	{
		if (AIController->LineOfSightTo(Player))
		{
			UE_LOG(LogTemp, Warning, TEXT("SET PLAYER"));
			BlackboardComponent->SetValueAsObject(GetSelectedBlackboardKey(), Player);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("CLEAR PLAYER"));
			BlackboardComponent->ClearValue(GetSelectedBlackboardKey());
		}
	}
}
