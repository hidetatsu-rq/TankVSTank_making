// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "NavModifierComponent.h"
#include "NavAreas/NavArea_Null.h"
#include "NavObject.generated.h"

UCLASS()
class TANKVSTANK_API ANavObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANavObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseComp;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* NavBlockComp;

	UPROPERTY(VisibleAnywhere)
	UNavModifierComponent* NavModifierComp;

};
