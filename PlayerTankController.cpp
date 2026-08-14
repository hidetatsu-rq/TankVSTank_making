// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTankController.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

void APlayerTankController::BeginPlay()
{
	Super::BeginPlay();

	SetPlayerCamera();
	bAutoManageActiveCameraTarget = false;
	if (PlayerTank)
	{
		PlayerTank->SetPlayerEnabled(false);
	}

	bShowMouseCursor = false;

	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(false);
	SetInputMode(InputMode);
	//SetInputMode(FInputModeGameOnly());
}

void APlayerTankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (PlayerTank->IsAlive)
	{
		FHitResult HitResult;
		GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		PlayerTank->RotateTurret(HitResult.ImpactPoint);
	}
	

}

void APlayerTankController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void APlayerTankController::SetPlayerCamera()
{
	TArray<AActor*> CameraActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActor);
	
	SetViewTargetWithBlend(CameraActor[0], 0.0f);

}


