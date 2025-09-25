// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Laser.generated.h"

class UPaperSpriteComponent;

UCLASS()
class TP1_PROG_LDROUHOT_API ALaser : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALaser();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprite")
	UPaperSpriteComponent* SpriteComponent;

protected:

	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed = 2000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Life")
	float LifeSeconds = 3.0f;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
