// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PathFindingSubsystem.h"
#include "SnakeAIPawn.h"
#include "SnakeGame/Definitions.h"
#include "Grid.h"
#include "SnakeAIController.generated.h"

UCLASS()
class SNAKEGAME_API ASnakeAIController : public AController
{
	GENERATED_BODY()
private:
	TArray<FTile> path;

	bool doOnce = true;

	int count = 0;

	ESnakeDirection direction = ESnakeDirection::None;

	UGridSubsystem* GridSubsystem;

	UPathFindingSubsystem* PathFindingSubsystem;

	ASnakeAIPawn* PawnAI = nullptr;

	FVector AppleVector;
public:
	// Sets default values for this actor's properties
	ASnakeAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	void SetDirections();
	
	void CalculatePath(ESnakeDirection Direction);

	static ESnakeDirection GetDirection(const FTile& Current, const FTile& Next);

	
};
