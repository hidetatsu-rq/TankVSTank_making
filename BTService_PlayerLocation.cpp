// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "AITankController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = TEXT("Get Player Location");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APawn* PlayerTankPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

	if (PlayerTankPawn && MyBlackboard)
	{
		MyBlackboard->SetValueAsVector(GetSelectedBlackboardKey(), PlayerTankPawn->GetActorLocation());
	}
}
