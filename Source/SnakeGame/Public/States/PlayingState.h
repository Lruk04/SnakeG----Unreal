// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "PlayingState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SNAKEGAME_API UPlayingState : public UStateBase, public IStateBase
{
	GENERATED_BODY()
public:
	int testVariable;
	
	virtual void EnterState_Implementation() override;
	virtual void ExitState_Implementation() override;
	virtual void UpdateState_Implementation(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "State", meta = (DisplayName = "On Enter Main Menu"))
	void ReceiveEnterState();

	UFUNCTION(BlueprintImplementableEvent, Category = "State", meta = (DisplayName = "On Exit Main Menu"))
	void ReceiveExitState();

	UFUNCTION(BlueprintImplementableEvent, Category = "State", meta = (DisplayName = "On Update Main Menu"))
	void ReceiveUpdateState(float DeltaTime);
};
