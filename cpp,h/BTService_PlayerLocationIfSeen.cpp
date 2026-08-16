// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "AITankController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update PlayerLocation If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAITankController* AITankController = Cast<AAITankController>(OwnerComp.GetAIOwner());
	if (AITankController)
	{
		ATank* PlayerTank = AITankController->PlayerTank;
		UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

		//PlayerTankがどうなると視界から消える判定になるのか(&& PlayerTank->IsAlive が必要なのかどうか)
		if (MyBlackboard && PlayerTank && PlayerTank->IsAlive)
		{

			if (AITankController->bCanSeePlayer)
			{
				MyBlackboard->SetValueAsVector(GetSelectedBlackboardKey(),PlayerTank->GetActorLocation());
				AITankController->SetFocus(PlayerTank);
			}
			else
			{
				MyBlackboard->ClearValue(GetSelectedBlackboardKey());
				AITankController->ClearFocus(EAIFocusPriority::Gameplay);
			}
		}
	}
}
