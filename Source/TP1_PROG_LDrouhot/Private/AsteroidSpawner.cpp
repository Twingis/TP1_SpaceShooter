// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidSpawner.h"
#include "Asteroid.h"
#include "PaperSpriteComponent.h"
#include "Engine/World.h"


// Sets default values
AAsteroidSpawner::AAsteroidSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AAsteroidSpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AAsteroidSpawner::SpawnAsteroid, SpawnInterval, true, 0.5f);
	
}

// Called every frame
void AAsteroidSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAsteroidSpawner::SpawnAsteroid()
{
    if (!AsteroidClass) return;
	
    FVector SpawnLocation;
    FVector2D ViewportSize;
    if (GEngine && GEngine->GameViewport)
    {
       GEngine->GameViewport->GetViewportSize(ViewportSize);
    }
    
    
    int32 Edge = FMath::RandRange(0, 3); // 0: Haut, 1: Droite, 2: Bas, 3: Gauche

    switch (Edge)
    {
    case 0:
       SpawnLocation.X = SpawnX;
       SpawnLocation.Y = FMath::RandRange(-ViewportSize.X / 2.f, ViewportSize.X / 2.f);
       SpawnLocation.Z = ViewportSize.Y / 2.f + 500.f; // 500.f est un offset pour être hors-écran
       break;
    case 1: 
       SpawnLocation.X = SpawnX;
       SpawnLocation.Y = ViewportSize.X / 2.f + 500.f;
       SpawnLocation.Z = FMath::RandRange(-ViewportSize.Y / 2.f, ViewportSize.Y / 2.f);
       break;
    case 2: 
       SpawnLocation.X = SpawnX;
       SpawnLocation.Y = FMath::RandRange(-ViewportSize.X / 2.f, ViewportSize.X / 2.f);
       SpawnLocation.Z = -ViewportSize.Y / 2.f - 500.f;
       break;
    case 3: 
       SpawnLocation.X = SpawnX;
       SpawnLocation.Y = -ViewportSize.X / 2.f - 500.f;
       SpawnLocation.Z = FMath::RandRange(-ViewportSize.Y / 2.f, ViewportSize.Y / 2.f);
       break;
    }
    
    
    FRotator SpawnRotation = GetActorRotation();
	
	
    FActorSpawnParameters SpawnParams;
    AAsteroid* NewAsteroid = GetWorld()->SpawnActor<AAsteroid>(AsteroidClass, SpawnLocation, SpawnRotation, SpawnParams);
	
    if (NewAsteroid)
    {
    	int32 RandomHP = FMath::RandRange(1, 3);
    	NewAsteroid->SetHealth(RandomHP);
    	
    	bool bGoToCenter = FMath::RandBool();

    	FVector Direction;

    	if (bGoToCenter)
    	{
    		FVector TargetLocation(
				0.f,
				FMath::RandRange(-ViewportSize.X / 4.f, ViewportSize.X / 4.f),
				FMath::RandRange(-ViewportSize.Y / 4.f, ViewportSize.Y / 4.f)
			);

    		Direction = (TargetLocation - SpawnLocation).GetSafeNormal();
    	}
    	else
    	{
    		int32 OtherEdge = FMath::RandRange(0, 3);

    		FVector OtherSpawnLocation = SpawnLocation;

    		switch (OtherEdge)
    		{
    		case 0: // Haut
    			OtherSpawnLocation = FVector(
					SpawnX,
					FMath::RandRange(-ViewportSize.X / 2.f, ViewportSize.X / 2.f),
					ViewportSize.Y / 2.f + 500.f
				);
    			break;
    		case 1: // Droite
    			OtherSpawnLocation = FVector(
					SpawnX,
					ViewportSize.X / 2.f + 500.f,
					FMath::RandRange(-ViewportSize.Y / 2.f, ViewportSize.Y / 2.f)
				);
    			break;
    		case 2: // Bas
    			OtherSpawnLocation = FVector(
					SpawnX,
					FMath::RandRange(-ViewportSize.X / 2.f, ViewportSize.X / 2.f),
					-ViewportSize.Y / 2.f - 500.f
				);
    			break;
    		case 3: // Gauche
    			OtherSpawnLocation = FVector(
					SpawnX,
					-ViewportSize.X / 2.f - 500.f,
					FMath::RandRange(-ViewportSize.Y / 2.f, ViewportSize.Y / 2.f)
				);
    			break;
    		}
    		
    		Direction = (OtherSpawnLocation - SpawnLocation).GetSafeNormal();
    	}
    	
    	if (NewAsteroid->SpriteComponent)
    	{
    		NewAsteroid->SpriteComponent->AddForce(Direction * Force, NAME_None, true);
    	}

    }
}
