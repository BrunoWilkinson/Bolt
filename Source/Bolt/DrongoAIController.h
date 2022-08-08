// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DrongoAIController.generated.h"

/**
 * 
 */
UCLASS()
class BOLT_API ADrongoAIController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;

public:
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
};
