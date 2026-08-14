// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TankVSTankGameInstance.h"
#include "StartWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANKVSTANK_API UStartWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* B_Start;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* B_Quit;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* T_Start;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* T_Quit;

	UFUNCTION()
	void StartClicked();

	UFUNCTION()
	void QuitClicked();

};
