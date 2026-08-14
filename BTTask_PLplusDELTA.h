// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_PLplusDELTA.generated.h"

/**
 * 
 */
UCLASS()
class TANKVSTANK_API UBTTask_PLplusDELTA : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_PLplusDELTA();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
