// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "AITankController.generated.h"

/**
 * 
 */
UCLASS()
class TANKVSTANK_API AAITankController : public AAIController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AAITankController();

	virtual void Tick(float DeltaTime) override;
	
	ATank* AITank;
	ATank* PlayerTank;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* EnemyAIBehaviorTree;

	

	void StartBehaviorTree();

	float NextShootTime = 0.0f;

	float SenseStartTime = 0.0f;
	float SenseDelay = 0.2f;

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerComp;

	UPROPERTY(VisibleAnywhere)
	UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	bool bCanSeePlayer = false;

	void ScanTurret(float DeltaTime);

	float ScanCenterYaw = 0.0f;
	float MinScanYaw = -45.0f;
	float MaxScanYaw = 45.0f;
	float ScanSpeed = 30.0f;     // 1秒に30度
	float ScanWaitTime = 3.0f;

	float ScanResumeTime = 0.0f;

	bool bScanToMax = true;
	bool bScanWaiting = false;
};
