// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScoreWidget.h"
#include "GameFramework/GameStateBase.h"
#include "GameStateSpace.generated.h"

/**
 * 
 */
UCLASS()
class TP1_PROG_LDROUHOT_API AGameStateSpace : public AGameStateBase
{
	GENERATED_BODY()

public:
	AGameStateSpace();
	
	UPROPERTY(BlueprintReadOnly, Category = "Score")
	int32 PlayerScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UScoreWidget> ScoreWidgetClass;
	
	UPROPERTY()
	UScoreWidget* ScoreWidgetInstance;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	void SetHealth(int32 NewHealth);
	void AddScore(int32 ScoreToAdd);
};
