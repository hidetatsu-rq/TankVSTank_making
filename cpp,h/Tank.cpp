// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerTankController.h"
#include "AITankController.h"
#include "TankVSTankGameMode.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(RootComp);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("PSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	MoveComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MoveComp"));


}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	OnTakeAnyDamage.AddDynamic(this, &ATank::OnDamageTaken);
	Health = MaxHealth;

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TankVelocity = GetVelocity();
	TankVelocity.Z = 0.0f;

	if (!TankVelocity.IsNearlyZero())
	{
		FRotator TankVelRot = FRotator(0.0f, TankVelocity.Rotation().Yaw, 0.0f);
		FRotator TargetBaseRot = FMath::RInterpTo(
			BaseMesh->GetComponentRotation(),
			TankVelRot,
			DeltaTime,
			5.0f
		);

		BaseMesh->SetWorldRotation(TargetBaseRot);
	}
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
		EIC->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::Fire);
	}
}

void ATank::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	if (TurretMesh)
	{
		OutLocation = TurretMesh->GetComponentLocation();
		OutRotation = TurretMesh->GetComponentRotation();
	}
}

void ATank::RotateTurret(FVector LookAtTarget)
{
	FVector DistBetTwoPoint = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator TargetRotation = FRotator(0.0f, DistBetTwoPoint.Rotation().Yaw, 0.0);

	FRotator InterpRotation = FMath::RInterpTo(
		TurretMesh->GetComponentRotation(),
		TargetRotation,
		GetWorld()->GetDeltaSeconds(),
		10.0f
	);

	TurretMesh->SetWorldRotation(InterpRotation);
}


void ATank::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	DoMove(MoveVector.X, MoveVector.Y);
}

void ATank::Fire()
{
	FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	if (Projectile)
	{
		Projectile->SetOwner(this);
		UE_LOG(LogTemp, Warning, TEXT("Fire Called"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Fire Called"));
	}

}

void ATank::DoMove(float Forward, float Right)
{
	if (GetController() != nullptr)
	{
		FRotator Rotation = GetController()->GetControlRotation();
		FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}

}

void ATank::OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsAlive)
	{
		if (Damage > 0.0f)
		{
			Health -= Damage;
			UE_LOG(LogTemp, Warning, TEXT("Damage: %f Health: %f"), Damage, Health);

			if (Health <= 0.0f)
			{
				IsAlive = false;
				Health = 0.0f;
				RootComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				if (APlayerTankController* PlayerTankController = Cast<APlayerTankController>(GetController()))
				{
					DetachFromControllerPendingDestroy();
				}
				
				ATankVSTankGameMode* TVTGameMode = Cast<ATankVSTankGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
				if (TVTGameMode)
				{
					TVTGameMode->ActorDied(DamagedActor);
				}
			}
		}
	}
}

void ATank::SetPlayerEnabled(bool Enabled)
{
	APlayerTankController* PTC = Cast<APlayerTankController>(GetController());
	if (PTC)
	{
		if (Enabled)
		{
			EnableInput(PTC);
		}
		else
		{
			DisableInput(PTC);
		}
		PTC->bShowMouseCursor = Enabled;
	}

}



