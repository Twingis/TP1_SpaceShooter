// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedCamera.h"


// Sets default values
AFixedCamera::AFixedCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
}

// Called when the game starts or when spawned
void AFixedCamera::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->SetViewTarget(this);
	}
	
}

// Called every frame
void AFixedCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

