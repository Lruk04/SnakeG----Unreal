#include "UWorldGenerator.h"
#include "SnakeGame/Public/UWorldGenerator.h"

#include "Grid.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "SnakeGame/Definitions.h"


UWorldGenerator::UWorldGenerator()
{
	GameGrid = Grid::GetInstance();

	
	
}

UWorldGenerator::~UWorldGenerator()
{
}

void UWorldGenerator::GenerateMap(const FString& FileName, const UWorldGenDataAsset* dataAsset) const
{
	

	//todo: read the files in the maps folder and give as a suggestion in a collection for the argument of generate map

	TArray<FString> Rows;
	const FString FilePath = FPaths::ProjectContentDir() + (TEXT("Maps/") + FileName + ".txt");

	if(FFileHelper::LoadFileToStringArray(Rows, *FilePath))
	{
		
		int y = 0;
		for(const FString& Row : Rows)
		{
			for(int x = 0; x < Row.Len(); x++)
			{
			
				FTransform Offset = FTransform(FRotator::ZeroRotator, FVector((Rows.Num() - y) * TileSize + 50, x * TileSize + 50, 0.0f));
				
				switch(Row[x])
				{
				case 'X':
					{
						
						GameGrid->SetTile(x, y, true);

						if (GEngine)
						{
							GEngine->AddOnScreenDebugMessage(
								/* Key */ -1, 
								/* TimeToDisplay */ 5.0f, 
								/* Color */ FColor::Green, 
								/* Message */ TEXT("SPAWN WALL")
							);
						}
						
						if (dataAsset == nullptr)
						{
							UE_LOG(LogTemp, Error, TEXT("Data asset is null"));
							return;
						}
						if (dataAsset->AWallMesh == nullptr) 
						{
							UE_LOG(LogTemp, Error, TEXT("Wall mesh is null"));
							return;
						}

						
						
						GetWorld()->SpawnActor(dataAsset->AWallMesh, &Offset);
					
						
					}
				case 'O':
					{
						/* Create a floor mesh that spawns below the wall height */
						//GameGrid->SetTile(x, y, false);
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
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				/* Key */ -1, 
				/* TimeToDisplay */ 5.0f, 
				/* Color */ FColor::Green, 
				/* Message */ TEXT("TRY ANYTHING")
			);
		}
	}
}

void UWorldGenerator::ClearMap() const
{
	//get rid of all meshes


	//Grid->Tiles.clear();

	GameGrid->ClearGrid();
}

void UWorldGenerator::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	
}