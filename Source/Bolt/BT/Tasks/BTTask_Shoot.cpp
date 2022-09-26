// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "../../Controllers/BotController.h"
#include "../../Characters/BotCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() != nullptr)
	{
		ABotCharacter* BotCharacter = Cast<ABotCharacter>(OwnerComp.GetAIOwner()->GetPawn());
		if (BotCharacter != nullptr)
		{
			BotCharacter->Shoot();
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
