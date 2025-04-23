// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UWorldGeneratorDataAsset.generated.h"

/**
 
*/
UCLASS()
class SNAKEGAME_API UWorldGeneratorDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldGenerator", meta = (AllowAbstract = false, BlueprintBaseOnly))
	TSubclassOf<AActor> WallMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldGenerator", meta = (AllowAbstract = false, BlueprintBaseOnly))
	TSubclassOf<AActor> FloorMesh;

	
};