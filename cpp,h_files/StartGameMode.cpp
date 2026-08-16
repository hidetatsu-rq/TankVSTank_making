// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameMode.h"
#include "Kismet/GameplayStatics.h"

void AStartGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC && StartWidgetClass)
	{
		StartWidget = CreateWidget<UStartWidget>(PC, StartWidgetClass);
		if (StartWidget)
		{
			StartWidget->AddToViewport();
		}

		PC->bShowMouseCursor = true;
		PC->CurrentMouseCursor = EMouseCursor::Default;
		PC->SetInputMode(FInputModeUIOnly());
	}
}
