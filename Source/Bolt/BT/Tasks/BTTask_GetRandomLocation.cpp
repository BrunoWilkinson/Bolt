// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetRandomLocation.h"
#include "../../Controllers/BotController.h"
#include "../../Characters/BotCharacter.h"
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
		ABotCharacter* BotCharacter = Cast<ABotCharacter>(OwnerComp.GetAIOwner()->GetPawn());
		UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
		if (BotCharacter != nullptr && BlackboardComponent != nullptr)
		{
			FNavLocation NavLocation;
			UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
			NavSys->GetRandomPointInNavigableRadius(BotCharacter->GetActorLocation(), Radius, NavLocation);
			BlackboardComponent->SetValueAsVector(TEXT("PatrolLocation"), NavLocation.Location);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
