#include "Laser.h"

#include "Asteroid.h"
#include "PaperSpriteComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ALaser::ALaser()
{
	PrimaryActorTick.bCanEverTick = true;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	RootComponent = SpriteComponent;
	
	SpriteComponent->SetGenerateOverlapEvents(true);
	
}

void ALaser::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
	
	FVector ForwardDirection = GetActorUpVector();
    
	
	FVector DeltaMovement = ForwardDirection * Speed * DeltaTime;

	
	AddActorWorldOffset(DeltaMovement, true);
}

void ALaser::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor && OtherActor != this)
		// Si c'est un laser, détruire les deux
			if  (OtherActor && OtherActor->IsA(AAsteroid::StaticClass()))
			{
			
				Destroy();
			
			}
}

