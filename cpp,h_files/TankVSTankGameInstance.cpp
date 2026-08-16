// Fill out your copyright notice in the Description page of Project Settings.


#include "TankVSTankGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UTankVSTankGameInstance::ChangeLevel(int32 Index)
{
	UE_LOG(LogTemp, Warning, TEXT("ChangeLevel: %d"), Index);

	if ((Index > 0) && (Index <= MaxLevelIndex))
	{
		CurrentLevelIndex = Index;

		FString LevelNameString = FString::Printf(TEXT("Level_%d"), CurrentLevelIndex);
		UE_LOG(LogTemp, Warning, TEXT("OpenLevel: %s"), *LevelNameString);

		UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelNameString));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Level Index"));
	}

	/*
	if ((Index > 0) && (Index <= MaxLevelIndex))
	{
		CurrentLevelIndex = Index;

		FString LevelNameString = FString::Printf(TEXT("Level_%d"), CurrentLevelIndex);
		UGameplayStatics::OpenLevel(GetWorld(), *LevelNameString);
	}
	*/
}

void UTankVSTankGameInstance::NextLevel()
{
	if (CurrentLevelIndex < MaxLevelIndex)
	{
		ChangeLevel(CurrentLevelIndex + 1);
	}
	else if (CurrentLevelIndex == MaxLevelIndex)
	{
		RestartGame();
	}
}

void UTankVSTankGameInstance::RetryLevel()
{
	ChangeLevel(CurrentLevelIndex);
}

void UTankVSTankGameInstance::RestartGame()
{
	ChangeLevel(1);
}


