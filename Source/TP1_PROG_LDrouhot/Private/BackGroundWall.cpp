// Fill out your copyright notice in the Description page of Project Settings.


#include "BackGroundWall.h"


// Sets default values
ABackGroundWall::ABackGroundWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
	RootComponent = WallMesh;
}

// Called when the game starts or when spawned
void ABackGroundWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABackGroundWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

