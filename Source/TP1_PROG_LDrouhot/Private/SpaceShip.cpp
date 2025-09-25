// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Laser.h" // include réel pour pouvoir SpawnActor<ALaser>



// Sets default values
ASpaceShip::ASpaceShip()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	RootComponent = SpriteComponent;

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = SpriteComponent;
	
}

// Called when the game starts or when spawned


// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpaceShip::MoveRightLeft(float X)
{
	if (X == 0.f) return;
	AddMovementInput(FVector(0.f, 1, 0), X*Speed);
}

void ASpaceShip::MoveUpDown(float X)
{
	if (X == 0.f) return;
	AddMovementInput(FVector(0.f, 0.f, 1), X*Speed);
}



void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
}

void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRightLeft", this, &ASpaceShip::MoveRightLeft);
	PlayerInputComponent->BindAxis("MoveUpDown", this, &ASpaceShip::MoveUpDown);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASpaceShip::Fire);
}

void ASpaceShip::Fire()
{
	if (LaserClass)
	{
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		
		FVector UpDirection = GetActorUpVector();

		SpawnLocation += UpDirection * SpawnOffset;
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		
		GetWorld()->SpawnActor<ALaser>(LaserClass, SpawnLocation, SpawnRotation, SpawnParams);
	}
}



