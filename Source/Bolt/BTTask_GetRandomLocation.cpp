// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetRandomLocation.h"
#include "DrongoAIController.h"
#include "AICharacter.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetRandomLocation::UBTTask_GetRandomLocation()
{
	NodeName = TEXT("Get Random Location");
}

EBTNodeResult::Type UBTTask_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() != nullptr)
	{
		AAICharacter* AICharacter = Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetPawn());
		UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
		if (AICharacter != nullptr && BlackboardComponent != nullptr)
		{
			FNavLocation NavLocation;
			UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
			NavSys->GetRandomPointInNavigableRadius(AICharacter->GetActorLocation(), Radius, NavLocation);
			BlackboardComponent->SetValueAsVector(TEXT("PatrolLocation"), NavLocation.Location);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
