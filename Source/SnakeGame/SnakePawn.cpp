// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakePawn.h"
#include "SnakePlayerState.h"
#include "SnakeBodyPart.h"

// Sets default values
ASnakePawn::ASnakePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	RootComponent = SceneComponent;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));

	CollisionComponent->SetupAttachment(RootComponent);
}

void ASnakePawn::PossessedBy(AController* NewController)
{
	SnakePlayerState = NewController->GetPlayerState<ASnakePlayerState>();

	if (!IsValid(SnakePlayerState))
	{
		UE_LOG(LogTemp, Error, TEXT("ASnakePawn::PossessedBy - Snake player state not valid!"));

		return;
	}
}

// Called when the game starts or when spawned
void ASnakePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(SnakePlayerState))
	{
		return;
	}

	UpdateFalling(DeltaTime);

	UpdateMovement(DeltaTime);
}

// Called to bind functionality to input
void ASnakePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	

}

void ASnakePawn::MoveSnake(float Distance)
{
	// Get snake location in the world
	FVector Position = GetActorLocation();
	// Update moving the snake
	switch (Direction)
	{
		case ESnakeDirection::Up:
			Position.X += Distance;
			break;
		case ESnakeDirection::Right:
			Position.Y += Distance;
			break;
		case ESnakeDirection::Down:
			Position.X -= Distance;
			break;
		case ESnakeDirection::Left:
			Position.Y -= Distance;
			break;
	}

	// Set snake location in the world
	SetActorLocation(Position);

	MovedTileDistance += Distance;
}

void ASnakePawn::UpdateMovement(float DeltaTime)
{
	// What the total distance the snake should move this frame is
	float TotalMoveDistance = SnakePlayerState->GetSnakeSpeed() * DeltaTime;

	// Distance that the snake have left to move this frame
	float MoveDistance = TotalMoveDistance;

	// While the distance left to move is more than what is left to move in the tile
	// The enter and move the distance that is left to move and then update direction.
	while (MovedTileDistance + MoveDistance >= TileSize)
	{
		// Update the move distance so that it is the same as what is left to move in the tile
		MoveDistance = TileSize - MovedTileDistance;

		// Move the snake that distance
		MoveSnake(MoveDistance);

		// Update snake direction
		UpdateDirection();

		// We need to decrease the total move distance with the moved distance
		TotalMoveDistance -= MoveDistance;

		// And set move distance of what is left of the total move distance
		MoveDistance = TotalMoveDistance;

		// Decrease moved tile distance with one tile size
		MovedTileDistance -= TileSize;

		// Pass position to children
		if (IsValid(ChildBodyPart))
		{
			ChildBodyPart->SetNextPosition(GetActorLocation());
		}
	
		
	}

	// If there are any move distance left, then move the snake that distance
	if (MoveDistance > 0.0f)
	{
		MoveSnake(MoveDistance);
	}
}

void ASnakePawn::UpdateFalling(float DeltaTime)
{
	// Get snake location in the world
	FVector Position = GetActorLocation();

	// Update speed
	VelocityZ -= 10.0f * DeltaTime;

	// Update falling
	Position.Z += VelocityZ;

	// Check floor collisions
	if (Position.Z <= 0.0f)
	{
		// Invert the position
		Position.Z = -Position.Z;

		// Invert and damp the velocity
		VelocityZ = -VelocityZ * 0.5f;

		if (FMath::Abs(VelocityZ) < 0.1f)
		{
			VelocityZ = 0.0f;

			Position.Z = 0.0f;

			bInAir = false;
		}
	}
	else
	{
		bInAir = true;
	}

	// Set snake location in the world
	SetActorLocation(Position);
}

void ASnakePawn::Jump()
{
	// Makes the snake jump (if it is not in the air)
	if (!bInAir)
	{
		VelocityZ = 10.0f;
	}
}

void ASnakePawn::UpdateDirection()
{
	if (DirectionQueue.IsEmpty())
	{
		return;
	}

	if (Direction != ESnakeDirection::None &&
	(static_cast<uint8>(Direction) + 2) % 4 == static_cast<uint8>(DirectionQueue[0]))
	{
		// Ignore the opposite direction
		DirectionQueue.RemoveAt(0);
		return;
	}

	Direction = DirectionQueue[0];
	DirectionQueue.RemoveAt(0);

	

	// Rotate the snake
	switch (Direction)
	{
	case ESnakeDirection::Up:
		ForwardRotation = FRotator(0.0f, 0.0f, 0.0f);
		
		break;
	case ESnakeDirection::Right:
		ForwardRotation = FRotator(0.0f, 90.0f, 0.0f);
		break;
	case ESnakeDirection::Down:
		ForwardRotation = FRotator(0.0f, 180.0f, 0.0f);
		break;
	case ESnakeDirection::Left:
		ForwardRotation = FRotator(0.0f, 270.0f, 0.0f);
		break;
	default: ;
	}
}

void ASnakePawn::SetNextDirection(ESnakeDirection InDirection)
{
	DirectionQueue.Add(InDirection);
}

void ASnakePawn::AteApple()
{
	UE_LOG(LogTemp, Log, TEXT("Apple eaten!"));

	FActorSpawnParameters SpawnParameters;

	SpawnParameters.Instigator = GetInstigator();

	ASnakeBodyPart* BodyPart = GetWorld()->SpawnActor<ASnakeBodyPart>(BodyPartClass, GetActorLocation(), GetActorRotation(), SpawnParameters);

	if (IsValid(ChildBodyPart))
	{
<<<<<<< HEAD
		ChildBodyPart->AddChildBodyPart(BodyPart);
=======
		ChildBodyPart->AddChildBodyPart(BodyPart, this);
>>>>>>> c07a0f259513bb480206b473059b372bcfec839a
	}
	else
	{
		ChildBodyPart = BodyPart;
	}
	
	// Send to the player state that an apple has been eaten
	SnakePlayerState->AddAppleEaten();
}