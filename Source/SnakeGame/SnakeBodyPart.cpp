// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakeBodyPart.h"
#include "SnakePlayerState.h"

// Sets default values
ASnakeBodyPart::ASnakeBodyPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	RootComponent = SceneComponent;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));

	CollisionComponent->SetupAttachment(RootComponent);
	
<<<<<<< HEAD
=======
	intOffset = -5;
	
>>>>>>> c07a0f259513bb480206b473059b372bcfec839a
	
}

// Called when the game starts or when spawned
void ASnakeBodyPart::BeginPlay()
{
	Super::BeginPlay();
	
	// Get player state
	SnakePlayerState = GetInstigatorController()->GetPlayerState<ASnakePlayerState>();

	if (!IsValid(SnakePlayerState))
	{
		UE_LOG(LogTemp, Error, TEXT("Super::BeginPlay - Snake player state not valid!"));

		return;
	}
}

// Called every frame
void ASnakeBodyPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(SnakePlayerState))
	{
		UE_LOG(LogTemp, Error, TEXT("ASnakeBodyPart::Tick - Snake player state not valid!"));

		return;
	}

	float Speed = SnakePlayerState->GetSnakeSpeed();
		
	
	
	if (NextPosition != FVector::ZeroVector)
	{
		FVector Position = GetActorLocation();
<<<<<<< HEAD
		
		FVector Forward = (NextPosition - Position).GetSafeNormal();;
=======

		FVector TargetPosition = NextPosition + Offset;

		
		
		// if(SnakePawn != nullptr && SnakePawn)
		// {
		// 	Forward = (TargetPosition - Position).GetSafeNormal();
		// 	if(GEngine)
		// 	{
		// 		GEngine->AddOnScreenDebugMessage(
		// 			/* Key */ -1,
		// 	/* TimeToDisplay */ 5.0f,
		// 	/* Color */ FColor::Green,
		// 	/* Message */ TEXT("NOT NORMAL ") 
		// 			);
		// 	}
		// }
		// else
		// {
		// 	Forward = (NextPosition - Position).GetSafeNormal();
		// 	if(GEngine)
		// 	{
		// 		GEngine->AddOnScreenDebugMessage(
		// 			/* Key */ -1,
		// 	/* TimeToDisplay */ 5.0f,
		// 	/* Color */ FColor::Green,
		// 	/* Message */ TEXT("NORMAL ") 
		// 			);
		// 	}
		// }
		FVector Forward = (NextPosition - Position).GetSafeNormal();
	
>>>>>>> c07a0f259513bb480206b473059b372bcfec839a
		
		Position += Forward * DeltaTime * Speed;

		SetActorLocation(Position);
	}
}

// void ASnakeBodyPart::SetNextPosition(const FVector& InPosition)
// {
// 	// Update the next position for this body part
// 	NextPosition = InPosition + GetOffset();
//
// 	// Pass the updated position to the child body part
// 	if (IsValid(ChildBodyPart))
// 	{
// 		ChildBodyPart->SetNextPosition(NextPosition);
// 	}
// }


void ASnakeBodyPart::SetNextPosition(const FVector& InPosition)
{
	if (IsValid(ChildBodyPart))
	{
		ChildBodyPart->SetNextPosition(NextPosition);
	}

	NextPosition = InPosition + GetOffset();
}

<<<<<<< HEAD

void ASnakeBodyPart::AddChildBodyPart(ASnakeBodyPart* InChildBodyPart)
=======
FVector ASnakeBodyPart::GetOffset() 
>>>>>>> c07a0f259513bb480206b473059b372bcfec839a
{

<<<<<<< HEAD
	
	if (IsValid(ChildBodyPart))
	{
		ChildBodyPart->AddChildBodyPart(InChildBodyPart);
		
=======

	switch (SnakePawn->Direction)
	{
	case ESnakeDirection::Up:
		Offset = FVector(-1.0f * static_cast<float>(intOffset), 0.0f, 0.0f);
		break;
	case ESnakeDirection::Right:
		Offset = FVector(0.0f, -1.0f * static_cast<float>(intOffset), 0.0f);
		break;
	case ESnakeDirection::Down:
		Offset = FVector(1.0f * static_cast<float>(intOffset), 0.0f, 0.0f);
		break;
	case ESnakeDirection::Left:
		Offset = FVector(0.0f, 1.0f * static_cast<float>(intOffset), 0.0f);
		break;
	default:
		Offset = FVector::ZeroVector;
		break;
	}

	return Offset;
}

// void ASnakeBodyPart::AddChildBodyPart(ASnakeBodyPart* InChildBodyPart, ASnakePawn* TempSnakePawn)
// {
// 	SnakePawn = TempSnakePawn;
//
// 	if (IsValid(ChildBodyPart))
// 	{
// 		// Pass the child body part down the chain
// 		ChildBodyPart->AddChildBodyPart(InChildBodyPart, SnakePawn);
// 	}
// 	else
// 	{
// 		// Set the new child body part
// 		ChildBodyPart = InChildBodyPart;
//
// 		// Calculate the cumulative offset for the new child body part
// 		Offset = GetOffset();
// 		FVector NewPosition = GetActorLocation() - Offset;
//
// 		// Set the position of the new child body part
// 		ChildBodyPart->SetActorLocation(NewPosition);
//
// 		// Pass the offset to the next child body part
// 		ChildBodyPart->intOffset = intOffset; // Ensure the offset value is consistent
// 	}
// }


void ASnakeBodyPart::AddChildBodyPart(ASnakeBodyPart* InChildBodyPart, ASnakePawn* TempSnakePawn)
{
	
	SnakePawn = TempSnakePawn;
	
	
	if (IsValid(ChildBodyPart))
	{
		ChildBodyPart->AddChildBodyPart(InChildBodyPart,SnakePawn);
>>>>>>> c07a0f259513bb480206b473059b372bcfec839a
	}
	else
	{
	
		ChildBodyPart = InChildBodyPart;

		ChildBodyPart->SetActorLocation(GetActorLocation());
	}
}