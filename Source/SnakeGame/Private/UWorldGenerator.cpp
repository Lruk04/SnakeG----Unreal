#include "UWorldGenerator.h"
#include "SnakeGame/Public/UWorldGenerator.h"

#include "SnakeGame/Definitions.h"


UWorldGenerator::UWorldGenerator()
{
	Grid = new FGrid();
}

UWorldGenerator::~UWorldGenerator()
{
}

void UWorldGenerator::GenerateMap(const FString& FileName) const
{
	if(!Grid->Tiles.empty()) { ClearMap(); }

	//todo: read the files in the maps folder and give as a suggestion in a collection for the argument of generate map

	TArray<FString> Rows;
	const FString FilePath = FPaths::ProjectContentDir() + (TEXT("../Maps/") + FileName);

	if(FFileHelper::LoadFileToStringArray(Rows, *FilePath))
	{
		int y = 0;
		for(const FString& Row : Rows)
		{
			for(int x = 0; x < Row.Len(); x++)
			{
				Grid->Tiles.emplace_back(FGrid::FTile(std::make_pair(x, y), 0, false, false));

				switch(Row[x])
				{
				case '#': Grid->Tiles.back().Occupied = true; Grid->Tiles.back().IsWall = true; break;
				case '.': /* Create a floor mesh that spawns below the wall height */ break;
				default: break;
				}
			}
			y++;
		}

		if (y != GWorld_Height)
		{
			UE_LOG(LogTemp, Error, TEXT("Map is not the correct height"));
			return;
		}

		//loop through all tiles and create the appropriate meshes for each of them

		Grid->Width = GWorld_Width;
		Grid->Height = GWorld_Height;
	}
}

void UWorldGenerator::ClearMap() const
{
	//get rid of all meshes
	Grid->Tiles.clear();
}

void UWorldGenerator::Initialize(FSubsystemCollectionBase& Collection) { Super::Initialize(Collection); }