#pragma once

#include "CoreMinimal.h"
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

	// Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed = 400.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<ALaser> LaserClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float SpawnOffset = 65.0f; 


protected:
	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaTime) override;
	void MoveRightLeft(float X);
	void MoveUpDown(float X);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Fire();
};
