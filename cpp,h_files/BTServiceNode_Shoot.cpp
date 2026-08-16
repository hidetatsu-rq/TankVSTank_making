// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceNode_Shoot.h"
#include "AITankController.h"
#include "Tank.h"

UBTServiceNode_Shoot::UBTServiceNode_Shoot()
{
	NodeName = TEXT("Shoot If Seen");
}

void UBTServiceNode_Shoot::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAITankController* AICon = Cast<AAITankController>(OwnerComp.GetAIOwner());
	if (AICon)
	{
		ATank* AITank = AICon->AITank;
		ATank* PlayerTank = AICon->PlayerTank;
		if (AITank && PlayerTank && PlayerTank->IsAlive)
		{
			const float CurrentTime = GetWorld()->GetTimeSeconds();
			if (CurrentTime >= AICon->NextShootTime)
			{
				if (AICon->LineOfSightTo(PlayerTank))
				{
					AITank->Fire();
					AICon->NextShootTime = CurrentTime + 3.0f;
				}
				
			}
		}
	}
}
