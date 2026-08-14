// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "Tank.h"
#include "PlayerTankController.generated.h"

/**
 * 
 */
UCLASS()
class TANKVSTANK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()

protected:
	void SetupInputComponent();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	void SetPlayerCamera();
	
	ATank* PlayerTank;
	
};
