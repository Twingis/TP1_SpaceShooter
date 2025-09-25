#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Pawn.h"
#include "SpaceShip.generated.h"

class UPaperSpriteComponent; // forward declaration
class ALaser;

UCLASS()
class TP1_PROG_LDROUHOT_API ASpaceShip : public APawn
{
	GENERATED_BODY()

public:
	ASpaceShip();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprite")
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	UPawnMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* CollisionComponent;

	// Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed = 400.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<ALaser> LaserClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float SpawnOffset = 65.0f;

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 Health = 3;

	bool bIsInvincible = false;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float InvincibilityTime = 1.0f;

	FTimerHandle InvincibilityTimerHandle;

	UPROPERTY(EditAnywhere, Category="Ship")
	float RotationSpeedDegPerSec = 360.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UUserWidget* GameOverWidgetInstance;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UNiagaraSystem* FireEffect;

protected:
	virtual void BeginPlay() override;

	FTimerHandle BlinkTimerHandle;
	
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float BlinkFrequency = 0.1f; // Clignote 10 fois par seconde
	
	void BlinkSprite();
	
	FVector2D ViewportSize;


public:
	virtual void Tick(float DeltaTime) override;
	void MoveRightLeft(float X);
	void MoveUpDown(float X);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void EndInvincibility();

	void HandleDamage();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void ShowGameOverScreen();

	void Fire();
};
