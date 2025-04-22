// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SnakePlayerState.generated.h"


/**
 * 
 */
UCLASS()
class SNAKEGAME_API ASnakePlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float SnakeSpeed = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int ApplesEaten = 0;

public:
	UFUNCTION(BlueprintCallable)
	float GetSnakeSpeed() const;

	UFUNCTION(BlueprintCallable)
	void IncreaseSnakeSpeed(float InAddSpeed);

	UFUNCTION(BlueprintCallable)
	void AddAppleEaten();
};
