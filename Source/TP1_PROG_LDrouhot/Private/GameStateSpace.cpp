// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateSpace.h"

#include "Blueprint/WidgetLayoutLibrary.h"


AGameStateSpace::AGameStateSpace()
{
	PlayerScore = 0;
}

void AGameStateSpace::BeginPlay()
{
	Super::BeginPlay();

	if (ScoreWidgetClass) 
	{
		ScoreWidgetInstance = CreateWidget<UScoreWidget>(GetWorld(), ScoreWidgetClass);
		if (ScoreWidgetInstance)
		{
			ScoreWidgetInstance->AddToViewport();
		}
	}
}

void AGameStateSpace::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogTemp, Warning, TEXT("EndPlay called on GameStateSpace"));
	Super::EndPlay(EndPlayReason);

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		
		PC->bShowMouseCursor = true;

		// Force l’enlèvement de tous les widgets
		UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	}
}

void AGameStateSpace::SetHealth(int32 NewHealth)
{
	if (ScoreWidgetInstance)
	{
		ScoreWidgetInstance->UpdateHealth(NewHealth);
	}
}

void AGameStateSpace::AddScore(int32 ScoreToAdd)
{
	PlayerScore += ScoreToAdd;

	if (ScoreWidgetInstance)
	{
		
		ScoreWidgetInstance->UpdateScore(PlayerScore);
	}
	
}
