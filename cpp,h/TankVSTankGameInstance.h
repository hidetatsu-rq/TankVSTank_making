// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TankVSTankGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TANKVSTANK_API UTankVSTankGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	int32 CurrentLevelIndex = 1;

	int32 MaxLevelIndex = 3;

	void ChangeLevel(int32 Index);

	void NextLevel();

	void RetryLevel();

	void RestartGame();
	
};
