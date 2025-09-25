// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "Laser.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
AAsteroid::AAsteroid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	RootComponent = SpriteComponent;

	SpriteComponent->SetSimulatePhysics(true);
	SpriteComponent->SetEnableGravity(false);
	SpriteComponent->SetGenerateOverlapEvents(false);
	SpriteComponent->BodyInstance.bUseCCD = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CatcherCollision"));
	CollisionComponent->SetupAttachment(SpriteComponent);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionComponent->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAsteroid::SetMovementDirection(FVector Direction)
{
	MovementDirection = Direction;
}



// ... (le reste de ton code)

void AAsteroid::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
    
	// S'assurer que l'autre acteur existe et n'est pas l'astéroïde actuel
	if (OtherActor && OtherActor != this)
	{
		// Si c'est un laser, détruire les deux
		if  (OtherActor && OtherActor->IsA(ALaser::StaticClass()))
		{
			Destroy();
		}
		else
		{
			// Sinon, si c'est un autre astéroïde, détruire les deux
			AAsteroid* OtherAsteroid = Cast<AAsteroid>(OtherActor);
			if (OtherAsteroid)
			{
				OtherAsteroid->Destroy();
				Destroy();
			}
		}
	}
}