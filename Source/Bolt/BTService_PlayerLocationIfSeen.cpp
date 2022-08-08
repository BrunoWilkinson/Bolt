// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "AICharacter.h"
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
		AAICharacter* AICharacter = Cast<AAICharacter>(AIController->GetPawn());
		if (AICharacter != nullptr)
		{
			if (AIController->LineOfSightTo(Player))
			{
				AICharacter->SetHasSeenPlayer(true);
				BlackboardComponent->SetValueAsObject(GetSelectedBlackboardKey(), Player);
			}
			else
			{
				AICharacter->SetHasSeenPlayer(false);
				BlackboardComponent->ClearValue(GetSelectedBlackboardKey());
			}
		}
	}
}
