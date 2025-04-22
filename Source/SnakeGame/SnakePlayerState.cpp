// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakePlayerState.h"
#include "SnakeGameMode.h"
#include "Kismet/GameplayStatics.h"

// float ASnakePlayerState::GetSnakeSpeed()
// {
// 	return SnakeSpeed;
// }

float ASnakePlayerState::GetSnakeSpeed() const
{
	// Provide the actual logic for returning the snake's speed
	return SnakeSpeed; // Assuming `SnakeSpeed` is a member variable
}

void ASnakePlayerState::IncreaseSnakeSpeed(float InAddSpeed)
{
	SnakeSpeed += InAddSpeed;
}

void ASnakePlayerState::AddAppleEaten()
{
	ApplesEaten++;

	ASnakeGameMode* SnakeGameMode = Cast<ASnakeGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!IsValid(SnakeGameMode))
	{
		UE_LOG(LogTemp, Error, TEXT("ASnakePawn::AteApple - Snake game mode not valid!"));

		return;
	}

	SnakeGameMode->AppleEaten(this);
}