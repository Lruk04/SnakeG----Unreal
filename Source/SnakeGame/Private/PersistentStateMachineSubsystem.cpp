// PersistentStateMachineSubsystem.cpp
#include "SnakeGame/Public/PersistentStateMachineSubsystem.h"

#include "SnakeGame/Public/States/MainMenuState.h"

void UPersistentStateMachineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogTemp, Log, TEXT("State Machine Subsystem Initialized"));
    
    // Start with Main Menu as default state
    ChangeState(UMainMenuState::StaticClass());
}

void UPersistentStateMachineSubsystem::Deinitialize()
{
    CleanupCurrentState();
    Super::Deinitialize();
    UE_LOG(LogTemp, Log, TEXT("State Machine Subsystem Deinitialized"));
}

void UPersistentStateMachineSubsystem::Tick(float DeltaTime)
{
   
    
    
    if (CurrentState && CurrentState->GetClass()->ImplementsInterface(UStateBase::StaticClass()))
    {
        IStateBase::Execute_UpdateState(CurrentState, DeltaTime);
    }
}

TStatId UPersistentStateMachineSubsystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(UPersistentStateMachineSubsystem, STATGROUP_Tickables);
}

void UPersistentStateMachineSubsystem::ChangeState(TSubclassOf<UStateBase> NewStateClass)
{
    if (!NewStateClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Attempted to change to null state class"));
        return;
    }

    if (!NewStateClass->ImplementsInterface(UStateBase::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("State class %s doesn't implement StateBase interface"), *NewStateClass->GetName());
        return;
    }

    // Clean up current state
    CleanupCurrentState();

    // Create and initialize new state
    CurrentState = NewObject<UObject>(this, NewStateClass);
    if (CurrentState)
    {
        IStateBase::Execute_EnterState(CurrentState);
        UE_LOG(LogTemp, Log, TEXT("Entered state: %s"), *NewStateClass->GetName());
    }
}

void UPersistentStateMachineSubsystem::CleanupCurrentState()
{
    if (CurrentState && CurrentState->GetClass()->ImplementsInterface(UStateBase::StaticClass()))
    {
        IStateBase::Execute_ExitState(CurrentState);
        UE_LOG(LogTemp, Log, TEXT("Exited state: %s"), *CurrentState->GetClass()->GetName());
    }
    CurrentState = nullptr;
}