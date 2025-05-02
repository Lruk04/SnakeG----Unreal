// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeAIController.h"

#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"


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

	

	
	GridSubsystem = GetWorld()->GetSubsystem<UGridSubsystem>();
	
	PathFindingSubsystem = GetWorld()->GetSubsystem<UPathFindingSubsystem>();
	
	AppleVector = FVector::ZeroVector;

	//
	// if (APawn* ControlledPawn = GetPawn())
	// {
	// 	PawnAI = Cast<ASnakeAIPawn>(ControlledPawn);
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Possessed"));
	// }
	//
}

void ASnakeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PawnAI = Cast<ASnakeAIPawn>(InPawn);


	

	
}

// Called every frame
void ASnakeAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	if (doOnce && PawnAI) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("CALCULATE!!!!!!!!!!!!!!"));
		CalculatePath(PawnAI->Direction);
		doOnce = false;
	}

	// if (FMath::IsNearlyEqual(PawnAI->GetActorLocation().X, AppleVector.X, 50) &&
	// FMath::IsNearlyEqual(PawnAI->GetActorLocation().Y, AppleVector.Y, 50))
	// {
	// 	doOnce = true;
	// }
	
}

void ASnakeAIController::SetDirections()
{
	for (count = 0; count < path.Num() - 1; ++count)
	{
		PawnAI->SetNextDirection(GetDirection(path[count], path[count + 1]));
	}

	
}

void ASnakeAIController::CalculatePath(ESnakeDirection Direction)
{
	if (GridSubsystem && PathFindingSubsystem && PawnAI)
	{
		
		FVector PawnLocation = PawnAI->GetActorLocation();

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, *FString::Printf(TEXT("Location: %s"), *PawnAI->GetActorLocation().ToString()));
		FTile CurrentTile = GridSubsystem->GetTile((PawnLocation.X-50) / 100, (PawnLocation.Y-50) / 100);
		
		
	
		
		 FTile TargetTile = GridSubsystem->GetRandomAppleTile();

		GEngine->AddOnScreenDebugMessage(
			-1, 
			5.0f, 
			FColor::Green, 
			*FString::Printf(TEXT("TargetTile Location: X=%d, Y=%d"), TargetTile.GetX(), TargetTile.GetY())
		);
		 
		 AppleVector = FVector(TargetTile.GetX() * 100 + 50, TargetTile.GetY() * 100 + 50, 0);
		 
		  // Find the path using A* algorithm
		  path = PathFindingSubsystem->FindPath(CurrentTile, TargetTile, Direction);
		 
		  if (path.IsEmpty())
		  {
		  
		  	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("No path found"));
		  	return;
		  }
		 //
		 // SetDirections();
	}
}

ESnakeDirection ASnakeAIController::GetDirection(const FTile& Current, const FTile& Next)
{
	if (Current.GetX() > Next.GetX() && Current.GetY() == Next.GetY())
	{
		return ESnakeDirection::Left;
	}
	if (Current.GetX() < Next.GetX() && Current.GetY() == Next.GetY())
	{
		return ESnakeDirection::Right;
	}
	if (Current.GetY() > Next.GetY() && Current.GetX() == Next.GetX())
	{
		return ESnakeDirection::Up;
	}
	if (Current.GetY() < Next.GetY() && Current.GetX() == Next.GetX())
	{
		return ESnakeDirection::Down;
	}
	return ESnakeDirection::None;
}





