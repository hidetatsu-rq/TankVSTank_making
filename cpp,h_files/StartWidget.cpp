// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidget.h"
#include "Kismet/KismetSystemLibrary.h"


void UStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (B_Start)
	{
		B_Start->OnClicked.AddDynamic(this, &UStartWidget::StartClicked);
		B_Start->SetVisibility(ESlateVisibility::Visible);
	}

	if (B_Quit)
	{
		B_Quit->OnClicked.AddDynamic(this, &UStartWidget::QuitClicked);
		B_Quit->SetVisibility(ESlateVisibility::Visible);
	}

	if (T_Start)
	{
		T_Start->SetText(FText::FromString("Start"));
	}

	if (T_Quit)
	{
		T_Quit->SetText(FText::FromString("Quit"));
	}
}


void UStartWidget::StartClicked()
{
	UTankVSTankGameInstance* TVTGI = Cast<UTankVSTankGameInstance>(GetGameInstance());
	if (TVTGI)
	{
		TVTGI->RestartGame();
	}
}

void UStartWidget::QuitClicked()
{
	{
		UKismetSystemLibrary::QuitGame(
			this,
			GetOwningPlayer(),
			EQuitPreference::Quit,
			false
		);
	}
}
