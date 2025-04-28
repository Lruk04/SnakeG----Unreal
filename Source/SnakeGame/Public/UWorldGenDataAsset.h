#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UWorldGenDataAsset.generated.h"

UCLASS(BlueprintType)
class SNAKEGAME_API UWorldGenDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldGenerator")
	TSubclassOf<AActor> AWallMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldGenerator")
	TSubclassOf<AActor> AFloorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldGenerator")
	TSubclassOf<AActor> AAppleMesh;
};