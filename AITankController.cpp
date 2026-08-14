// Fill out your copyright notice in the Description page of Project Settings.


#include "AITankController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


AAITankController::AAITankController()
{
	//下の二つはAI上で設定する視野や音の感知設定
	AIPerComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerComp"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConf"));
	SightConfig->SightRadius = 20000.0f;
	SightConfig->LoseSightRadius = 25000.0f;
	SightConfig->PeripheralVisionAngleDegrees = 45.0f;

	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerComp->ConfigureSense(*SightConfig);

	//AIPerComp->SetDominantSense(SightConfig->GetSenseImplementation());

}

void AAITankController::BeginPlay()
{
	Super::BeginPlay();

	AIPerComp->OnTargetPerceptionUpdated.AddDynamic(this, &AAITankController::OnTargetPerceptionUpdated);
}


void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (AITank && PlayerTank)
	{
		if (bCanSeePlayer)
		{
			bScanWaiting = false;
			AITank->RotateTurret(PlayerTank->GetActorLocation());
		}
		else
		{
			UBlackboardComponent* MyBlackboard = GetBlackboardComponent();
			if (MyBlackboard && MyBlackboard->IsVectorValueSet("LastKnowPlayerLocation"))
			{
				bScanWaiting = false;
				FVector LastKnowPlayerLocation = MyBlackboard->GetValueAsVector("LastKnowPlayerLocation");
				AITank->RotateTurret(LastKnowPlayerLocation);
			}
			else
			{
				ScanTurret(DeltaTime);
			}
		}
	}
}


void AAITankController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor == PlayerTank)
	{
		bCanSeePlayer = Stimulus.WasSuccessfullySensed();
	}
}

void AAITankController::ScanTurret(float DeltaTime)
{
	if (AITank && AITank->TurretMesh)
	{
		const float CurrentTime = GetWorld()->GetTimeSeconds();

		if (bScanWaiting)
		{
			if (CurrentTime >= ScanResumeTime)
			{
				bScanWaiting = false;
			}
		}

		if (!bScanWaiting)
		{
			const float TargetOffset = bScanToMax ? MaxScanYaw : MinScanYaw;

			FRotator CurrentRotation = AITank->TurretMesh->GetRelativeRotation();

			const float CurrentOffset = FMath::FindDeltaAngleDegrees(
				ScanCenterYaw,
				CurrentRotation.Yaw
			);

			const float NewOffset =FMath::FInterpConstantTo(
				CurrentOffset,
				TargetOffset,
				DeltaTime,
				ScanSpeed
			);

			CurrentRotation.Yaw = ScanCenterYaw + NewOffset;

			AITank->TurretMesh->SetRelativeRotation(CurrentRotation);

			if (FMath::IsNearlyEqual(NewOffset,TargetOffset,0.1f))
			{
				bScanWaiting = true;
				ScanResumeTime = CurrentTime + ScanWaitTime;

				bScanToMax = !bScanToMax;
			}
		}
	}
}


void AAITankController::StartBehaviorTree()
{

	if (EnemyAIBehaviorTree)
	{
		RunBehaviorTree(EnemyAIBehaviorTree);

		AITank = Cast<ATank>(GetPawn());
		UBlackboardComponent* MyBlackboard = GetBlackboardComponent();
		if (MyBlackboard)
		{
			if (AITank)
			{
				MyBlackboard->SetValueAsVector("StartLocation", AITank->GetActorLocation());
				UE_LOG(LogTemp, Warning, TEXT("Blackboard is available"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed AITank"));

			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed MyBlackboard"));

		}

		
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed RunBehaviorTree"));

	}
	
}



