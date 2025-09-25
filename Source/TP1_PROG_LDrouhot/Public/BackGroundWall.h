// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BackGroundWall.generated.h"

UCLASS()
class TP1_PROG_LDROUHOT_API ABackGroundWall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABackGroundWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wall", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WallMesh;
};
