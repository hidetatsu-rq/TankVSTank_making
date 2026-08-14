// Fill out your copyright notice in the Description page of Project Settings.

#include "TankVSTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "AITankController.h"
#include "PlayerTankController.h"

ATankVSTankGameMode::ATankVSTankGameMode()
{
}

void ATankVSTankGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	if (PlayerTank)
	{
		APlayerTankController* PlayerTankController = Cast<APlayerTankController>(PlayerTank->GetController());
		if (PlayerTankController)
		{
			PlayerTankController->PlayerTank = PlayerTank;
			ScreenMessageWidget = CreateWidget<UScreenMessage>(PlayerTankController, ScreenMessageClass);
			if (ScreenMessageWidget)
			{
				ScreenMessageWidget->AddToPlayerScreen();
				ScreenMessageWidget->ScreenMessageText("GetReady...");
			}
		}

		TArray<AActor*> EnemyTankActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAITankController::StaticClass(), EnemyTankActors);
		EnemyTankCounts = EnemyTankActors.Num();

		for (AActor* EnemyTankActor : EnemyTankActors)
		{
			AAITankController* AITankController = Cast<AAITankController>(EnemyTankActor);
			if (AITankController)
			{
				AITankController->PlayerTank = PlayerTank;

				AITankController->StartBehaviorTree();
				UE_LOG(LogTemp, Warning, TEXT("Success StartBehaviorTree"));
			}

			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Fail StartBehaviorTree"));
			}
		}
	}

	CountdownSeconds = CountdownDelay;
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ATankVSTankGameMode::OnCountdownTimerTimeout, 1.0f, true);
	
}

void ATankVSTankGameMode::Tick(float DeltaTime)
{
}

void ATankVSTankGameMode::ActorDied(AActor* DeadTankActor)
{
	bool IsGameOver = false;
	if (DeadTankActor == PlayerTank)
	{
		IsGameOver = true;
		PlayerTank->Destroy();
	}
	else
	{
		ATank* DeadTank = Cast<ATank>(DeadTankActor);
		if (DeadTank)
		{
			AAITankController* AITankController = Cast<AAITankController>(DeadTank->GetController());
			if (AITankController)
			{
				DeadTank->Destroy();
				EnemyTankCounts--;
				UE_LOG(LogTemp, Warning, TEXT("%d"), EnemyTankCounts);
				if (EnemyTankCounts == 0)
				{
					IsGameOver = true;
					IsVictory = true;
				}
			}
		}
	}

	if (IsGameOver)
	{
		FString GameOverString = IsVictory ? "Victory" : "Defeat";

		ScreenMessageWidget->ScreenMessageText(GameOverString);
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Visible);
		ScreenMessageWidget->ShowGameOverButton(IsVictory);

		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC)
		{
			PC->bShowMouseCursor = true;
			PC->CurrentMouseCursor = EMouseCursor::Default;
			PC->SetInputMode(FInputModeUIOnly());
		}
	}
}


void ATankVSTankGameMode::OnCountdownTimerTimeout()
{
	CountdownSeconds--;

	if (CountdownSeconds > 0)
	{
		ScreenMessageWidget->ScreenMessageText(FString::FromInt(CountdownSeconds));
	}
	else if (CountdownSeconds == 0)
	{
		if (PlayerTank)
		{
			PlayerTank->SetPlayerEnabled(true);
		}
		ScreenMessageWidget->ScreenMessageText("Go!!");
	}
	else if(CountdownSeconds < 0)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
