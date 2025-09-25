// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class TP1_PROG_LDROUHOT_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category="Score")
	void UpdateScore(int32 Total);

	UFUNCTION(BlueprintImplementableEvent, Category="Score")
	void UpdateHealth(int32 Total);
};
