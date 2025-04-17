// PersistentStateMachineSubsystem.h
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SnakeGame/Public/States/StateBase.h"
#include "PersistentStateMachineSubsystem.generated.h"

UCLASS()
class SNAKEGAME_API UPersistentStateMachineSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	//~ Begin USubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//~ End USubsystem Interface

	//~ Begin FTickableGameObject Interface
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return bIsActive; }
	virtual TStatId GetStatId() const override;
	virtual bool IsTickableWhenPaused() const override { return true; }
	virtual bool IsTickableInEditor() const override { return false; }
	//~ End FTickableGameObject Interface

	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void ChangeState(TSubclassOf<UStateBase> NewStateClass);

	UFUNCTION(BlueprintCallable, Category = "State Machine")
	UObject* GetCurrentState() const { return CurrentState; }

	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void SetActive(bool bActive) { bIsActive = bActive; }

private:
	UPROPERTY()
	UObject* CurrentState = nullptr;

	UPROPERTY()
	bool bIsActive = true;

	void CleanupCurrentState();
};