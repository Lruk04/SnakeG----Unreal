#include "PathFindingSubsystem.h"
#include "Grid.h"
#include "SnakeGame/Definitions.h"

UPathFindingSubsystem::UPathFindingSubsystem()
    : GridSubsystem(nullptr)
{
}

void UPathFindingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    // Get the GridSubsystem
    GridSubsystem = GetWorld()->GetSubsystem<UGridSubsystem>();
    if (!GridSubsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to initialize GridSubsystem in PathFindingSubsystem."));
    }
}

TArray<FTile> UPathFindingSubsystem::FindPath(const FTile& Start, const FTile& Goal, ESnakeDirection Direction)
{
    if (!GridSubsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("GridSubsystem is not initialized."));
        return {};
    }

    TArray<FTile*> OpenList;
    TArray<FTile*> ClosedList;

    FTile* StartTile = &GridSubsystem->GetTile(Start.GetX(), Start.GetY());
    FTile* GoalTile = &GridSubsystem->GetTile(Goal.GetX(), Goal.GetY());

    StartTile->Parent = nullptr;
    StartTile->GCost = 0;
    StartTile->HCost = GetDistance(*StartTile, *GoalTile);
    StartTile->FCost = StartTile->GCost + StartTile->HCost;

    OpenList.Add(StartTile);

    while (OpenList.Num() > 0)
    {
        FTile* CurrentTile = OpenList[0];
        for (FTile* Tile : OpenList)
        {
            if (Tile->GetFCost() < CurrentTile->GetFCost() ||
                (Tile->GetFCost() == CurrentTile->GetFCost() && Tile->HCost < CurrentTile->HCost))
            {
                CurrentTile = Tile;
            }
        }

        OpenList.Remove(CurrentTile);
        ClosedList.Add(CurrentTile);

        if (CurrentTile == GoalTile)
        {
            return RetracePath(CurrentTile);
        }

        for (FTile& Neighbour : FindNeighbours(Direction, *CurrentTile))
        {
            if (ClosedList.Contains(&Neighbour) || Neighbour.IsOccupied() || Neighbour.IsSnake())
            {
                continue;
            }

            int32 NewCost = CurrentTile->GCost + GetDistance(*CurrentTile, Neighbour);
            if (NewCost < Neighbour.GCost || !OpenList.Contains(&Neighbour))
            {
                Neighbour.GCost = NewCost;
                Neighbour.HCost = GetDistance(Neighbour, *GoalTile);
                Neighbour.FCost = Neighbour.GCost + Neighbour.HCost;
                Neighbour.Parent = CurrentTile;

                if (!OpenList.Contains(&Neighbour))
                {
                    OpenList.Add(&Neighbour);
                }
            }
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("No path found."));
    return {};
}

int32 UPathFindingSubsystem::GetDistance(const FTile& A, const FTile& B) const
{
    return FMath::Abs(A.GetX() - B.GetX()) + FMath::Abs(A.GetY() - B.GetY());
}

TArray<FTile> UPathFindingSubsystem::RetracePath(FTile* Current) const
{
    TArray<FTile> Path;
    while (Current)
    {
        Path.Add(*Current);
        Current = Current->Parent;
    }
    Algo::Reverse(Path);
    return Path;
}

TArray<FTile> UPathFindingSubsystem::FindNeighbours(ESnakeDirection Direction, const FTile& CurrentTile) const
{
    TArray<FTile> Neighbours;

    TArray<FIntPoint> Directions = {
        FIntPoint(0, 1),  // Up
        FIntPoint(1, 0),  // Right
        FIntPoint(0, -1), // Down
        FIntPoint(-1, 0)  // Left
    };

    for (const FIntPoint& Dir : Directions)
    {
        int32 NewX = CurrentTile.GetX() + Dir.X;
        int32 NewY = CurrentTile.GetY() + Dir.Y;

        if (NewX >= 0 && NewX < GWorld_Width && NewY >= 0 && NewY < GWorld_Height)
        {
            Neighbours.Add(GridSubsystem->GetTile(NewX, NewY));
        }
    }

    return Neighbours;
}