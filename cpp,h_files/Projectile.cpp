// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectimeMesh"));
	SetRootComponent(ProjectileMesh);

	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MoveComp"));
	MoveComp->InitialSpeed = 1000.0f;
	MoveComp->MaxSpeed = 1000.0f;

	MoveComp->ProjectileGravityScale = 0.0f;
	MoveComp->bShouldBounce = true;
	MoveComp->Bounciness = 1.0f;
	MoveComp->Friction = 0.0f;

	MoveComp->bRotationFollowsVelocity = true;
	MoveComp->bRotationRemainsVertical = true;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	ECollisionChannel HitChannel = OtherComp->GetCollisionObjectType();

	if (HitChannel == ECC_Pawn)
	{
		//&& (OtherActor != MyOwner) 
		if (OtherActor && (OtherActor != this))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetActorNameOrLabel());
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, UDamageType::StaticClass());
		}
		Destroy();
	}

	if (HitChannel == ECC_WorldStatic)
	{
		WorldStaticHitCount++;
		if (WorldStaticHitCount >= MaxHitCount)
		{
			Destroy();
		}
	}
	
}


