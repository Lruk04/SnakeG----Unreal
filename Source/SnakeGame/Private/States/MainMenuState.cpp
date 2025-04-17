// MainMenuState.cpp
#include "SnakeGame/Public/States/MainMenuState.h"

void UMainMenuState::EnterState_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("MainMenuState: Enter"));
	ReceiveEnterState();
}

void UMainMenuState::ExitState_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("MainMenuState: Exit"));
	ReceiveExitState();
}

void UMainMenuState::UpdateState_Implementation(float DeltaTime)
{
	testVariable += 1;
	UE_LOG(LogTemp, Log, TEXT("MainMenuState: Update"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, *FString::Printf(TEXT("MainMenuState: Update %d"), testVariable));
	}
	
	ReceiveUpdateState(DeltaTime);
}