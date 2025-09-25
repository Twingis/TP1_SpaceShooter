// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "PaperSprite.h"
#include "GameStateSpace.h"
#include "Laser.h"
#include "PaperSpriteComponent.h"
#include "SpaceShip.h"
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

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("AsteroidCollision"));
	CollisionComponent->SetupAttachment(SpriteComponent);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionComponent->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	if (!CollisionComponent)
	{
		CollisionComponent = FindComponentByClass<UBoxComponent>();
	}

	RotationSpeed = FMath::RandRange(-120.f, 120.f);

	
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpriteComponent)
	{
		FRotator Rot = SpriteComponent->GetComponentRotation();
		Rot.Pitch += RotationSpeed * DeltaTime; 
		SpriteComponent->SetWorldRotation(Rot);
	}
}

void AAsteroid::SetHealth(int32 NewHealth)
{
	Health = NewHealth;
	InitialHealth = NewHealth;
	UpdateSpriteBasedOnHealth();
	
}

void AAsteroid::UpdateSpriteBasedOnHealth()
{
	if (!SpriteComponent)
	{
		return;
	}

	UPaperSprite* NewSprite = nullptr;

	if (InitialHealth <= 1)
	{
		NewSprite = SpriteForHP1;
	}
	else if (InitialHealth == 2)
	{
		NewSprite = SpriteForHP2;
	}
	else 
	{
		NewSprite = SpriteForHP3;
	}

	
	if (NewSprite)
	{
		SpriteComponent->SetSprite(NewSprite);
		FBoxSphereBounds SpriteBounds = SpriteComponent->CalcLocalBounds();
		FVector BoxExtent = SpriteBounds.BoxExtent;

		// 🔹 Optionnel : agrandir légèrement la hitbox
		float CollisionScale = 1.1f;
		BoxExtent *= CollisionScale;

		CollisionComponent->SetBoxExtent(BoxExtent, true);
		CollisionComponent->SetRelativeLocation(FVector::ZeroVector);

	}
}



void AAsteroid::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
    
	
	if (OtherActor && OtherActor != this)
	{
		if  (OtherActor && OtherActor->IsA(ALaser::StaticClass()))
		{
			Health--;
			AGameStateSpace* GameState = GetWorld()->GetGameState<AGameStateSpace>();
			if (Health <= 0)
			{
				if (ExplosionEffect)
				{
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(
						GetWorld(),
						ExplosionEffect,
						GetActorLocation(),
						FRotator::ZeroRotator
					);
				}
				GameState->AddScore(InitialHealth * 100);
				Destroy();
			}
			
		}
		else
		{
			if  (OtherActor && OtherActor->IsA(ASpaceShip::StaticClass()))
			{
				if (ExplosionEffect)
				{
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(
						GetWorld(),
						ExplosionEffect,
						GetActorLocation(),
						FRotator::ZeroRotator
					);
				}
				Destroy();
			}
			
		}
	}
}