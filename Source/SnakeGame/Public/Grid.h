#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Grid.generated.h"

USTRUCT(BlueprintType)
struct FTile
{
    GENERATED_BODY()

private:
    int32 X, Y;
    char Symbol;
    bool bOccupied;
    bool bSnake;
    bool bFood;

public:
    FTile() : X(0), Y(0), Symbol('O'), bOccupied(false), bSnake(false), bFood(false) {}
    FTile(int32 InX, int32 InY, char InSymbol) : X(InX), Y(InY), Symbol(InSymbol), bOccupied(false), bSnake(false), bFood(false) {}

    UPROPERTY(BlueprintReadOnly, Category = "Tile")
    int32 HCost;

    UPROPERTY(BlueprintReadOnly, Category = "Tile")
    int32 GCost;

    UPROPERTY(BlueprintReadOnly, Category = "Tile")
    int32 FCost;

    FTile* Parent = nullptr;

    int32 GetFCost() const { return FCost + HCost; }
    int32 GetX() const { return X; }
    int32 GetY() const { return Y; }

    char GetSymbol() const { return Symbol; }
    void SetSymbol(char NewSymbol) { Symbol = NewSymbol; }

    bool IsOccupied() const { return bOccupied; }
    void SetOccupied(bool bIsOccupied) { bOccupied = bIsOccupied; }

    bool IsSnake() const { return bSnake; }
    void SetSnake(bool bIsSnake) { bSnake = bIsSnake; }

    bool IsFood() const { return bFood; }
    void SetFood(bool bIsFood) { bFood = bIsFood; }
};

UCLASS(Blueprintable)
class SNAKEGAME_API UGridSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

private:
    TArray<TArray<FTile>> Grid;
    int32 Width;
    int32 Height;

public:
    UGridSubsystem();
    
    UFUNCTION(BlueprintCallable, Category = "Grid")
    void InitializeGrid(int32 InWidth, int32 InHeight);

    UFUNCTION(BlueprintCallable, Category = "Grid")
    FTile& GetTile(int32 X, int32 Y);

    UFUNCTION(BlueprintCallable, Category = "Grid")
    void SetTile(int32 X, int32 Y, bool bOccupied);

    UFUNCTION(BlueprintCallable, Category = "Grid")
    void SetTileFood(int32 X, int32 Y, bool bFood);

    UFUNCTION(BlueprintCallable, Category = "Grid")
    void SetTileSnake(int32 X, int32 Y, bool bSnake);

    UFUNCTION(BlueprintCallable, Category = "Grid")
    void ClearGrid();

    UFUNCTION(BlueprintCallable, Category = "Grid")
    FTile& GetRandomUnoccupiedTile();

    UFUNCTION(BlueprintCallable, Category = "Grid")
    FTile& GetRandomAppleTile();

    UFUNCTION(BlueprintCallable, Category = "Grid")
    void PrintGrid() const;
};