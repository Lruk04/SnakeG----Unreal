#include "UWorldGenerator.h"
#include "SnakeGame/Public/UWorldGenerator.h"

#include "Grid.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "SnakeGame/Definitions.h"


UWorldGenerator::UWorldGenerator()
{
	GameGrid = Grid::GetInstance();


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	WallMeshInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("WallMeshInstances"));
	WallMeshInstances->SetupAttachment(RootComponent);

	
	
}

UWorldGenerator::~UWorldGenerator()
{
}

void UWorldGenerator::GenerateMap(const FString& FileName) const
{
	

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
				switch(Row[x])
				{
				case 'X':
					{
						/* Create a wall mesh that spawns at the wall height */
						GameGrid->SetTile(x, y, true);

						FVector WorldLocation = FVector(x * TileSize + 50, y * TileSize + 50, 10);
						FTransform InstanceTransform;
						InstanceTransform.SetLocation(WorldLocation);
						WallMeshInstances->AddInstance(InstanceTransform);
						break;
					}
				case 'O':
					{
						/* Create a floor mesh that spawns below the wall height */
						GameGrid->SetTile(x, y, false);
					}

					break;
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


		
		// Grid->Width = GWorld_Width;
		// Grid->Height = GWorld_Height;
	}
}

void UWorldGenerator::ClearMap() const
{
	//get rid of all meshes


	//Grid->Tiles.clear();

	GameGrid->ClearGrid();
}

void UWorldGenerator::Initialize(FSubsystemCollectionBase& Collection) { Super::Initialize(Collection); }