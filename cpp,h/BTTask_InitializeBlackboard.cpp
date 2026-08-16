// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_InitializeBlackboard.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_InitializeBlackboard::UBTTask_InitializeBlackboard()
{
	NodeName = TEXT("Int BB Kye");
}

EBTNodeResult::Type UBTTask_InitializeBlackboard::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	if (MyBlackboard)
	{
		MyBlackboard->ClearValue("LastKnowPlayerLocation");
		MyBlackboard->SetValueAsBool("IsBTInitialized",true);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
