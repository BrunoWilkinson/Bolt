// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "DrongoAIController.h"
#include "AICharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() != nullptr)
	{
		AAICharacter* AICharacter = Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetPawn());
		if (AICharacter != nullptr)
		{
			AICharacter->Shoot();
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
