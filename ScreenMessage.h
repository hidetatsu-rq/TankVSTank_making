// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/BackgroundBlur.h"
#include "ScreenMessage.generated.h"

/**
 * 
 */
UCLASS()
class TANKVSTANK_API UScreenMessage : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ScreenMessageBlock;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* T_NextOrRetry;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* T_Quit;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* B_NextOrRetry;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* B_Quit;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBackgroundBlur* Blur_IsGameOver;

	void ScreenMessageText(FString Message);

	void ShowGameOverButton(bool bVictory);

	virtual void NativeConstruct() override;

	bool bIsVictory = false;

	UFUNCTION()
	void OnNextOrRetryClicked();

	UFUNCTION()
	void OnQuitClicked();

};
