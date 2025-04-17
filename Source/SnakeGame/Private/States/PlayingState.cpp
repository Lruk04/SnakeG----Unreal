// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGame/Public/States//PlayingState.h"


void UPlayingState::EnterState_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("PlayingState: Enter"));
	ReceiveEnterState();
}

void UPlayingState::ExitState_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("PlayingState: Exit"));
	ReceiveExitState();
}

void UPlayingState::UpdateState_Implementation(float DeltaTime)
{
	testVariable += 1;
	UE_LOG(LogTemp, Log, TEXT("PlayingState: Update"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, *FString::Printf(TEXT("PlayingState: Update %d"), testVariable));
	}

	ReceiveUpdateState(DeltaTime);
}