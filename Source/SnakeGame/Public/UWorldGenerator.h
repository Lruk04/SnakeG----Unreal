#pragma once
#include "UWorldGenerator.generated.h"

UCLASS(Blueprintable)
class UWorldGenerator final : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	class FGrid
	{
	public:
		class FTile
		{
			std::pair<int, int> Position;

		public:
			float Value;
			bool Occupied;
			bool IsWall;

			explicit FTile(const std::pair<int, int> Position, const float Value = 0.0f, const bool bOccupied = false, const bool bIsWall = false) :
				Position(Position), Value(Value), Occupied(bOccupied), IsWall(bIsWall) {};

			std::pair<int, int> GetPosition() const { return Position; };
		};

		int Width = 0;
		int Height = 0;

		std::vector<FTile> Tiles; //x position + (width * y)
	};

	FGrid* Grid;

	UWorldGenerator();
	virtual ~UWorldGenerator() override;

	UFUNCTION(BlueprintCallable, Category = "WorldGenerator")
	void GenerateMap(const FString& FileName) const;

	UFUNCTION(BlueprintCallable, Category = "WorldGenerator")
	void ClearMap() const;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};