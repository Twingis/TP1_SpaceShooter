// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidSpawner.generated.h"

UCLASS()
class TP1_PROG_LDROUHOT_API AAsteroidSpawner : public AActor
{
	GENERATED_BODY()

public:
	AAsteroidSpawner();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	void SpawnAsteroid();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<class AAsteroid> AsteroidClass;

	// X Position
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnX = -25.f;

	FTimerHandle SpawnTimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnInterval = 0.75f;

	// Initial Force
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float Force = 50000.f;
};
