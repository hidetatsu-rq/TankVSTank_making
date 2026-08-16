// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"
#include "AITankController.h"
#include "Tank.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
	NodeName = TEXT("ShootTask");
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	AAITankController* OwnerController = Cast<AAITankController>(OwnerComp.GetAIOwner());
	if (OwnerController)
	{
		ATank* PlayerTank = OwnerController->PlayerTank;
		ATank* OwnerTank = OwnerController->AITank;
		if (OwnerTank && PlayerTank && PlayerTank->IsAlive)
		{
			OwnerTank->Fire();
			Result = EBTNodeResult::Succeeded;
		}
	}

	return Result;
}
