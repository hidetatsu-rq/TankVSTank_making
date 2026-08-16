// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenMessage.h"
#include "TankVSTankGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

void UScreenMessage::ScreenMessageText(FString Message)
{
	FText MessageText = FText::FromString(Message);
	ScreenMessageBlock->SetText(MessageText);
}


void UScreenMessage::NativeConstruct()
{
	Super::NativeConstruct();

	if (B_NextOrRetry)
	{
		B_NextOrRetry->OnClicked.AddDynamic(this, &UScreenMessage::OnNextOrRetryClicked);
		B_NextOrRetry->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	if (B_Quit)
	{
		B_Quit->OnClicked.AddDynamic(this, &UScreenMessage::OnQuitClicked);
		B_Quit->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	if (Blur_IsGameOver)
	{
		Blur_IsGameOver->SetVisibility(ESlateVisibility::Collapsed);
	}
	
}

void UScreenMessage::OnNextOrRetryClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("NextOrRetry Clicked"));

	UTankVSTankGameInstance* TVTGI = Cast<UTankVSTankGameInstance>(GetGameInstance());
	if (TVTGI)
	{
		if (bIsVictory)
		{
			UE_LOG(LogTemp, Warning, TEXT("NextLevel"));
			TVTGI->NextLevel();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("RetryLevel"));
			TVTGI->RetryLevel();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed GameInstance Cast"));
	}

	/*
	UTankVSTankGameInstance* TVTGI = Cast<UTankVSTankGameInstance>(GetGameInstance());
	if (TVTGI)
	{
		if (bIsVictory)
		{
			TVTGI->NextLevel();
		}
		else
		{
			TVTGI->RetryLevel();
		}
	}
	*/
}

void UScreenMessage::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(
		this,
		GetOwningPlayer(),
		EQuitPreference::Quit,
		false
	);
}


void UScreenMessage::ShowGameOverButton(bool bVictory)
{
	bIsVictory = bVictory;

	if (B_NextOrRetry)
	{
		B_NextOrRetry->SetVisibility(ESlateVisibility::Visible);
	}

	if (B_Quit)
	{
		B_Quit->SetVisibility(ESlateVisibility::Visible);
	}

	if (Blur_IsGameOver)
	{
		Blur_IsGameOver->SetVisibility(ESlateVisibility::HitTestInvisible);
	}

	if (T_NextOrRetry)
	{
		T_NextOrRetry->SetText(bVictory ? FText::FromString("Next") : FText::FromString("Retry"));
	}

	if (T_Quit)
	{
		T_Quit->SetText(FText::FromString("Quit"));
	}
	
}