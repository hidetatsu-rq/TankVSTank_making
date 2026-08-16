// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StartWidget.h"
#include "StartGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TANKVSTANK_API AStartGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UStartWidget> StartWidgetClass;

	UStartWidget* StartWidget;
};
