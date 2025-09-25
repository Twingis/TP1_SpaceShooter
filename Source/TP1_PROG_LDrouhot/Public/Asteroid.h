// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Asteroid.generated.h"

class UPaperSpriteComponent;

UCLASS()
class TP1_PROG_LDROUHOT_API AAsteroid : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAsteroid();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprite")
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* CollisionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed = 200.f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 Health = 2;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Asteroid|Visual")
	UPaperSprite* SpriteForHP1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Asteroid|Visual")
	UPaperSprite* SpriteForHP2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Asteroid|Visual")
	UPaperSprite* SpriteForHP3;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 InitialHealth = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Asteroid")
	float RotationSpeed = 90.f;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UNiagaraSystem* ExplosionEffect;


protected:

	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetHealth(int32 NewHealth);
	void UpdateSpriteBasedOnHealth();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
