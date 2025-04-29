// Fill out your copyright notice in the Description page of Project Settings.


#include "Apple.h"

#include "Grid.h"
#include "UWorldGenerator.h"


// Sets default values
AApple::AApple()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AApple::AppleDestroy()
{
	if (UWorldGenerator* WorldGenerator = Cast<UWorldGenerator>(GetWorld()->GetSubsystem<UWorldGenerator>()))
	{
		WorldGenerator->SpawnApple(WorldGenerator->WorldGenDataAsset);
	}

	UGridSubsystem* GridSubsystem = GetWorld()->GetSubsystem<UGridSubsystem>();

	GridSubsystem->GetTile((GetActorTransform().GetLocation().X - 50) / 100, (GetActorTransform().GetLocation().Y - 50) / 100).SetFood(false);

	Destroy();
}

// Called when the game starts or when spawned
void AApple::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


