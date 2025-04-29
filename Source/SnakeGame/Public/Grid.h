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
    FTile();
    FTile(int32 InX, int32 InY, char InSymbol);

    UPROPERTY(BlueprintReadOnly, Category = "Tile")
    int32 HCost;

    UPROPERTY(BlueprintReadOnly, Category = "Tile")
    int32 GCost;

    UPROPERTY(BlueprintReadOnly, Category = "Tile")
    int32 FCost;

    FTile* Parent;

    int32 GetFCost() const;
    int32 GetX() const;
    int32 GetY() const;

    char GetSymbol() const;
    void SetSymbol(char NewSymbol);

    bool IsOccupied() const;
    void SetOccupied(bool bIsOccupied);

    bool IsSnake() const;
    void SetSnake(bool bIsSnake);

    bool IsFood() const;
    void SetFood(bool bIsFood);
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