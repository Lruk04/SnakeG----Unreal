#include "UWorldGenerator.h"
#include "SnakeGame/Public/UWorldGenerator.h"

#include "Grid.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "SnakeGame/Definitions.h"


UWorldGenerator::UWorldGenerator()
{
	
}
void UWorldGenerator::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
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
			
				FTransform Offset = FTransform(FRotator::ZeroRotator, FVector(x* TileSize + 50, y * TileSize + 50, 0.0f));
				
				switch(Row[x])
				{
					case 'X':
						{
							if (GridSubsystem)
							{
								GridSubsystem->SetTile(x, y , true);	
								
							}
							else
							{
								UE_LOG(LogTemp, Error, TEXT("GridSubsystem is not initialized."));
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
	//GridSubsystem->ClearGrid();
	
}

void UWorldGenerator::SetSubSystem()
{



	//GridSubsystem = Cast<UGridSubsystem>(SubsystemObject);
	GridSubsystem = GetWorld()->GetSubsystem<UGridSubsystem>();
	if (GridSubsystem)
	{
		GridSubsystem->InitializeGrid(GWorld_Width, GWorld_Height);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to cast subsystem to UGridSubsystem."));
	}
}

void UWorldGenerator::SpawnApple(const UWorldGenDataAsset* dataAsset) const
{
	int x = 0;
	int y = 0;
	auto& newPos = GridSubsystem->GetRandomUnoccupiedTile();
	
	x = newPos.GetX();
	y = newPos.GetY();
	FTransform Offset = FTransform(FRotator::ZeroRotator, FVector(x * TileSize + 50, y * TileSize + 50, 0.0f));
	GridSubsystem->SetTileFood(x, y, true);
	GetWorld()->SpawnActor(dataAsset->AAppleMesh, &Offset); 

	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			/* Key */ -1, 
			/* TimeToDisplay */ 5.0f, 
			/* Color */ FColor::Green, 
			/* Message */ *FString::Printf(TEXT("Apple Spawned at (%d, %d)"), x, y)
		);
	}

	if(GEngine && GridSubsystem->GetTile(x,y).IsOccupied())
	{
		
		GEngine->AddOnScreenDebugMessage(
			/* Key */ -1, 
			/* TimeToDisplay */ 5.0f, 
			/* Color */ FColor::Green, 
			/* Message */ *FString::Printf(TEXT("engine is stupid" ))
		);
	}
	GridSubsystem->PrintGrid();
	
}

void UWorldGenerator::SetAssetData(const UWorldGenDataAsset* dataAsset)
{
	WorldGenDataAsset = dataAsset;
	if (WorldGenDataAsset)
	{
		UE_LOG(LogTemp, Log, TEXT("Data asset set successfully."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to set data asset."));
	}
}

