// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameMode.h"
#include "SnakePlayerState.h"

void ASnakeGameMode::AppleEaten(ASnakePlayerState* SnakePlayerState)
{
	SnakePlayerState->IncreaseSnakeSpeed(100.0f);
}