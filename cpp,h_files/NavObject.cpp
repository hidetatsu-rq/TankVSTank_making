// Fill out your copyright notice in the Description page of Project Settings.


#include "NavObject.h"

// Sets default values
ANavObject::ANavObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	BaseComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseComp"));
	BaseComp->SetupAttachment(RootComp);

	NavBlockComp = CreateDefaultSubobject<UBoxComponent>(TEXT("NavBlockComp"));
	NavBlockComp->SetupAttachment(RootComp);
	NavBlockComp->SetBoxExtent(FVector(200.0f, 200.0f, 200.0f));
	NavBlockComp->SetCanEverAffectNavigation(true);

	NavModifierComp = CreateDefaultSubobject<UNavModifierComponent>(TEXT("NavModifierComp"));
	NavModifierComp->SetAreaClass(UNavArea_Null::StaticClass());


}

// Called when the game starts or when spawned
void ANavObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANavObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

