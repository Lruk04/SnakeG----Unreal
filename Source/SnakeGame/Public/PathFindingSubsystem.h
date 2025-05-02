#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

#include "PathFindingSubsystem.generated.h"

class AGrid;
UCLASS(Blueprintable)
class SNAKEGAME_API UPathFindingSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

private:
    UPROPERTY()
    UGridSubsystem* GridSubsystem;
    bool bFirstPathing = false;

public:
    UPathFindingSubsystem();

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    UFUNCTION(BlueprintCallable, Category = "PathFinding")
    TArray<FTile> FindPath(const FTile& Start, const FTile& Goal, ESnakeDirection Direction);

private:
    static int32 GetDistance(const FTile& A, const FTile& B);
    static TArray<FTile> RetracePath(const FTile* Current);
    TArray<FTile> FindNeighbours(ESnakeDirection Direction, const FTile& CurrentTile) const;
};