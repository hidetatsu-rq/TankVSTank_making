// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PLplusDELTA.h"
#include "Kismet/GameplayStatics.h"

UBTTask_PLplusDELTA::UBTTask_PLplusDELTA()
{
	NodeName = TEXT("PlayerLocation + Δ");
}

EBTNodeResult::Type UBTTask_PLplusDELTA::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* PlayerTankPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	FVector PlayerLocation = PlayerTankPawn->GetActorLocation();

	/*
	if (MyBlackboard && PlayerTankPawn)
	{
		MyBlackboard->SetValueAsVector(GetSelectedBlackboardKey(), );
	}
	*/

	EBTNodeResult::Type Result = EBTNodeResult::Succeeded;
	return Result;
}
