// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"

#include "Asteroid.h"
#include "GameOver.h"
#include "GameStateSpace.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Laser.h" // include réel pour pouvoir SpawnActor<ALaser>
#include "PaperSprite.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"


// Sets default values
ASpaceShip::ASpaceShip()
{
	PrimaryActorTick.bCanEverTick = true;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	RootComponent = SpriteComponent;
	SpriteComponent->SetGenerateOverlapEvents(false);

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ShipCollision"));
	CollisionComponent->SetupAttachment(SpriteComponent);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionComponent->SetGenerateOverlapEvents(true);

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = SpriteComponent;
	
}


void ASpaceShip::BlinkSprite()
{
	if (SpriteComponent)
	{
		SpriteComponent->SetVisibility(!SpriteComponent->IsVisible());
	}
}


void ASpaceShip::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!MovementComponent) return;

    FVector Velocity = MovementComponent->Velocity;

    
    if (Velocity.IsNearlyZero(1e-3f))
    {
        return;
    }

   
    float Y = Velocity.Y;
    float Z = Velocity.Z;
    float AbsY = FMath::Abs(Y);
    float AbsZ = FMath::Abs(Z);

   
    float DesiredPitch = 0.f;

    if (AbsY > AbsZ)
    {
        
        if (Y > 0.f)
        {
            
            DesiredPitch = -90.f;
        }
        else
        {
           
            DesiredPitch = 90.f;
        }
    }
    else
    {
       
        if (Z > 0.f)
        {
            DesiredPitch = 0.f;
        }
        
    }
	
    FRotator CurrentRot = GetActorRotation();
	
    RotationSpeedDegPerSec = RotationSpeedDegPerSec > 0.f ? RotationSpeedDegPerSec : 360.f;
   
    float MaxDelta = RotationSpeedDegPerSec * DeltaTime;

    
    float NewPitch = FMath::FixedTurn(CurrentRot.Pitch, DesiredPitch, MaxDelta);

    FRotator NewRot = CurrentRot;
    NewRot.Pitch = NewPitch;
    
    SetActorRotation(NewRot);

	FVector CurrentLocation = GetActorLocation();
    
	// 2. Obtient la taille actuelle du Viewport
    
	// 3. Obtient la taille du composant (sprite ou collision)
	// Utilise GetScaledBoxExtent() pour la collision box si tu en as une, ou GetScaledSpriteSize()
	// pour le sprite. C'est l'approche la plus fiable.
	FVector ActorSize = CollisionComponent->GetScaledBoxExtent();

	// 4. Calcule les limites de l'écran centrées sur l'origine
	float ViewportHalfWidth = ViewportSize.X / 2.f;
	float ViewportHalfHeight = ViewportSize.Y / 2.f;

	// 5. Calcule les demi-tailles de l'acteur pour le décalage
	float ActorHalfWidth = ActorSize.X; // GetScaledBoxExtent retourne déjà une demi-taille
	float ActorHalfHeight = ActorSize.Y;
    
	// 6. Clamp les coordonnées de l'acteur pour le maintenir dans l'écran
	CurrentLocation.Y = FMath::Clamp(CurrentLocation.Y, -ViewportHalfWidth , ViewportHalfWidth - ActorHalfWidth);
	CurrentLocation.Z = FMath::Clamp(CurrentLocation.Z, -ViewportHalfHeight , ViewportHalfHeight - ActorHalfHeight);

	// 7. Applique la nouvelle position
	SetActorLocation(CurrentLocation);
	
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

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}
}

void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRightLeft", this, &ASpaceShip::MoveRightLeft);
	PlayerInputComponent->BindAxis("MoveUpDown", this, &ASpaceShip::MoveUpDown);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASpaceShip::Fire);
}

void ASpaceShip::EndInvincibility()
{
	bIsInvincible = false;

	GetWorld()->GetTimerManager().ClearTimer(BlinkTimerHandle);
	
	if (SpriteComponent)
	{
		SpriteComponent->SetVisibility(true);
	}
	
}

void ASpaceShip::HandleDamage()
{
	if (!bIsInvincible)
	{
		Health--;
		
		bIsInvincible = true;
		
		GetWorld()->GetTimerManager().SetTimer(InvincibilityTimerHandle, this, &ASpaceShip::EndInvincibility, InvincibilityTime, false);

		GetWorld()->GetTimerManager().SetTimer(BlinkTimerHandle, this, &ASpaceShip::BlinkSprite, BlinkFrequency, true);

		AGameStateSpace* GameState = GetWorld()->GetGameState<AGameStateSpace>();
		if (GameState)
		{
			GameState->SetHealth(Health);
		}
	}
}

void ASpaceShip::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor && OtherActor != this)
			if  (OtherActor && OtherActor->IsA(AAsteroid::StaticClass()))
			{
				HandleDamage();
				if (Health <= 0)
				{
					ShowGameOverScreen();
					Destroy();
				}
			}
}

void ASpaceShip::ShowGameOverScreen()
{
	if (GameOverWidgetClass && GetWorld())
	{
		GameOverWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
		if (GameOverWidgetInstance)
		{
			AGameStateSpace* GameState = GetWorld()->GetGameState<AGameStateSpace>();

			
			if (UGameOver* GameOverWidget = Cast<UGameOver>(GameOverWidgetInstance))
			{
				if (GameState)
				{
					
					GameOverWidget->DisplayFinalScore(GameState->PlayerScore);
				}
			}
			
			GameOverWidgetInstance->AddToViewport();

			
			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (PC)
			{
				PC->bShowMouseCursor = true;
				PC->SetInputMode(FInputModeUIOnly());
			}
		}
	}
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

		if (FireEffect)
		{
			FRotator EffectRotation = SpawnRotation;
			EffectRotation.Pitch += 90.f;

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				GetWorld(),
				FireEffect,
				SpawnLocation,
				EffectRotation
			);
		}
		
		GetWorld()->SpawnActor<ALaser>(LaserClass, SpawnLocation, SpawnRotation, SpawnParams);
	}
}



