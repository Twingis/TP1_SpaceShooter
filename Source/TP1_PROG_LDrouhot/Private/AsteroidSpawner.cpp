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
    // Vérifie que la classe de l'astéroïde est bien assignée
    if (!AsteroidClass) return;

    // 1. Détermine la position de spawn aléatoire
    FVector SpawnLocation;
    FVector2D ViewportSize;
    if (GEngine && GEngine->GameViewport)
    {
       GEngine->GameViewport->GetViewportSize(ViewportSize);
    }
    
    // Choisir un bord de l'écran au hasard
    int32 Edge = FMath::RandRange(0, 3); // 0: Haut, 1: Droite, 2: Bas, 3: Gauche

    switch (Edge)
    {
    case 0: // Haut
       SpawnLocation.X = -25.f;
       SpawnLocation.Y = FMath::RandRange(-ViewportSize.X / 2.f, ViewportSize.X / 2.f);
       SpawnLocation.Z = ViewportSize.Y / 2.f + 500.f; // 500.f est un offset pour être hors-écran
       break;
    case 1: // Droite
       SpawnLocation.X = -25.f;
       SpawnLocation.Y = ViewportSize.X / 2.f + 500.f;
       SpawnLocation.Z = FMath::RandRange(-ViewportSize.Y / 2.f, ViewportSize.Y / 2.f);
       break;
    case 2: // Bas
       SpawnLocation.X = -25.f;
       SpawnLocation.Y = FMath::RandRange(-ViewportSize.X / 2.f, ViewportSize.X / 2.f);
       SpawnLocation.Z = -ViewportSize.Y / 2.f - 500.f;
       break;
    case 3: // Gauche
       SpawnLocation.X = -25.f;
       SpawnLocation.Y = -ViewportSize.X / 2.f - 500.f;
       SpawnLocation.Z = FMath::RandRange(-ViewportSize.Y / 2.f, ViewportSize.Y / 2.f);
       break;
    }
    
    
    FRotator SpawnRotation = GetActorRotation();
	
	
    FActorSpawnParameters SpawnParams;
    AAsteroid* NewAsteroid = GetWorld()->SpawnActor<AAsteroid>(AsteroidClass, SpawnLocation, SpawnRotation, SpawnParams);

    // 4. Calcule et assigne une direction de mouvement à l'astéroïde
    if (NewAsteroid)
    {
        FVector TargetLocation(0.f, FMath::RandRange(-ViewportSize.X / 4.f, ViewportSize.X / 4.f), FMath::RandRange(-ViewportSize.Y / 4.f, ViewportSize.Y / 4.f));
    	
        FVector Direction = (TargetLocation - SpawnLocation).GetSafeNormal();
    	
    	NewAsteroid->SpriteComponent->AddForce(Direction * Force, NAME_None, true);
    }
}
