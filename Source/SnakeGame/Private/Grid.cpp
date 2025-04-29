#include "Grid.h"

FTile::FTile() : X(0), Y(0), Symbol('O'), bOccupied(false), bSnake(false), bFood(false) {}

FTile::FTile(int32 InX, int32 InY, char InSymbol)
    : X(InX), Y(InY), Symbol(InSymbol), bOccupied(false), bSnake(false), bFood(false) {}

int32 FTile::GetFCost() const { return FCost + HCost; }
int32 FTile::GetX() const { return X; }
int32 FTile::GetY() const { return Y; }

char FTile::GetSymbol() const { return Symbol; }
void FTile::SetSymbol(char NewSymbol) { Symbol = NewSymbol; }

bool FTile::IsOccupied() const { return bOccupied; }
void FTile::SetOccupied(bool bIsOccupied) { bOccupied = bIsOccupied; }

bool FTile::IsSnake() const { return bSnake; }
void FTile::SetSnake(bool bIsSnake) { bSnake = bIsSnake; }

bool FTile::IsFood() const { return bFood; }
void FTile::SetFood(bool bIsFood) { bFood = bIsFood; }

UGridSubsystem::UGridSubsystem()
{

    
    
}

void UGridSubsystem::InitializeGrid(int32 InWidth, int32 InHeight)
{
    Width = InWidth;
    Height = InHeight;

    // Resize the grid to match the specified dimensions
    Grid.SetNum(Height);
    for (int32 Y = 0; Y < Height; ++Y)
    {
        Grid[Y].SetNum(Width);
        for (int32 X = 0; X < Width; ++X)
        {
            Grid[Y][X] = FTile(X, Y, 'O'); // Initialize each tile with default values
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Grid initialized with dimensions: %d x %d"), Width, Height);
}

FTile& UGridSubsystem::GetTile(int32 X, int32 Y)
{
    return Grid[Y][X];
}

void UGridSubsystem::SetTile(int32 X, int32 Y, bool bOccupied)
{
    Grid[Y][X].SetOccupied(bOccupied);
    Grid[Y][X].SetSymbol('X');
}

void UGridSubsystem::SetTileFood(int32 X, int32 Y, bool bFood)
{
    Grid[Y][X].SetFood(bFood);
}

void UGridSubsystem::SetTileSnake(int32 X, int32 Y, bool bSnake)
{
    Grid[Y][X].SetSnake(bSnake);
}

void UGridSubsystem::ClearGrid()
{
    for (int32 Y = 0; Y < Height; ++Y)
    {
        for (int32 X = 0; X < Width; ++X)
        {
            Grid[Y][X].SetOccupied(false);
            Grid[Y][X].SetFood(false);
            Grid[Y][X].SetSnake(false);
        }
    }
}

FTile& UGridSubsystem::GetRandomUnoccupiedTile()
{
    int32 RandomX = 0;
    int32 RandomY = 0;

    int Attempts = 0;
    do
    {
        Attempts++;
        RandomX = FMath::RandRange(0, Width - 1);
        RandomY = FMath::RandRange(0, Height - 1);

        // Debugging: Log the tile state
        const FTile& Tile = GetTile(RandomX, RandomY);
        UE_LOG(LogTemp, Log, TEXT("Checking tile at (%d, %d): IsOccupied=%s, IsSnake=%s, IsFood=%s, Attempts=%d"),
            RandomX, RandomY,
            Tile.IsOccupied() ? TEXT("true") : TEXT("false"),
            Tile.IsSnake() ? TEXT("true") : TEXT("false"),
            Tile.IsFood() ? TEXT("true") : TEXT("false"),
            Attempts
            );

        if (Tile.IsOccupied())
        {
           
        }
    } while (Grid[RandomY][RandomX].IsOccupied() || Grid[RandomY][RandomX].IsSnake() || Grid[RandomY][RandomX].IsFood());

    return Grid[RandomY][RandomX];
}

FTile& UGridSubsystem::GetRandomAppleTile()
{
    TArray<FTile*> AppleTiles;

    for (int32 Y = 0; Y < Height; ++Y)
    {
        for (int32 X = 0; X < Width; ++X)
        {
            if (Grid[Y][X].IsFood())
            {
                AppleTiles.Add(&Grid[Y][X]);
            }
        }
    }

    if (AppleTiles.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("No apple tile found"));
        throw std::runtime_error("No apple tile found");
    }

    int32 RandomIndex = FMath::RandRange(0, AppleTiles.Num() - 1);
    return *AppleTiles[RandomIndex];
}

void UGridSubsystem::PrintGrid() const
{
    UE_LOG(LogTemp, Log, TEXT("Grid System:"));
    for (const auto& Row : Grid)
    {
        FString RowString;
        for (const auto& Tile : Row)
        {
            RowString += Tile.GetSymbol();
            RowString += ' ';
        }
        UE_LOG(LogTemp, Log, TEXT("%s"), *RowString);
    }
    // UE_LOG(LogTemp, Log, TEXT("Grid System:"));
    // for (const auto& Row : Grid)
    // {
    //     FString RowString;
    //     for (const auto& Tile : Row)
    //     {
    //         RowString += Tile.IsOccupied() ? 'X' : 'O';
    //         RowString += ' ';
    //     }
    //     UE_LOG(LogTemp, Log, TEXT("%s"), *RowString);
    // }
}