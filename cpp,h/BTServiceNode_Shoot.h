// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTServiceNode_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class TANKVSTANK_API UBTServiceNode_Shoot : public UBTService
{
	GENERATED_BODY()

public:
	UBTServiceNode_Shoot();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
