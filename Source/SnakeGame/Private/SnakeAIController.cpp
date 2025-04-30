// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeAIController.h"

#include "SnakeAIPawn.h"


// Sets default values
ASnakeAIController::ASnakeAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASnakeAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakeAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASnakeAIController::MoveToDirection(ESnakeDirection Direction) const
{
	if (ASnakeAIPawn* PawnAi = Cast<ASnakeAIPawn>(GetPawn()))
	{
		PawnAi->SetNextDirection(Direction);
	}
}

