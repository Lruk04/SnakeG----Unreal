#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Grid.h"
#include "PathFindingSubsystem.generated.h"

UCLASS(Blueprintable)
class SNAKEGAME_API UPathFindingSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

private:
    UPROPERTY()
    UGridSubsystem* GridSubsystem;

public:
    UPathFindingSubsystem();

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    UFUNCTION(BlueprintCallable, Category = "PathFinding")
    TArray<FTile> FindPath(const FTile& Start, const FTile& Goal, ESnakeDirection Direction);

private:
    int32 GetDistance(const FTile& A, const FTile& B) const;
    TArray<FTile> RetracePath(FTile* Current) const;
    TArray<FTile> FindNeighbours(ESnakeDirection Direction, const FTile& CurrentTile) const;
};