// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tank.h"
#include "ScreenMessage.h"
#include "TankVSTankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TANKVSTANK_API ATankVSTankGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ATankVSTankGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 EnemyTankCounts;

	void ActorDied(AActor* DamagedTankActor);

	bool IsVictory = false;

	ATank* PlayerTank;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UScreenMessage> ScreenMessageClass;

	UScreenMessage* ScreenMessageWidget;

	FTimerHandle CountdownTimerHandle;

	int32 CountdownSeconds;
	int32 CountdownDelay = 4;

	void OnCountdownTimerTimeout();
	
};
