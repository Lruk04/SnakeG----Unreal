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
	
	intOffset = -20;
	
	
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

	
	
	if(SnakePawn != nullptr && SnakePawn)
	{
		Offset = GetOffset();
	}
	
		
	
	
	if (NextPosition != FVector::ZeroVector)
	{
		FVector Position = GetActorLocation();

		FVector TargetPosition = NextPosition + Offset;

		FVector Forward;
		
		if(SnakePawn != nullptr && SnakePawn)
		{
			Forward = (TargetPosition - Position).GetSafeNormal();
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					/* Key */ -1,
			/* TimeToDisplay */ 5.0f,
			/* Color */ FColor::Green,
			/* Message */ TEXT("NOT NORMAL ") 
					);
			}
		}
		else
		{
			Forward = (NextPosition - Position).GetSafeNormal();
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					/* Key */ -1,
			/* TimeToDisplay */ 5.0f,
			/* Color */ FColor::Green,
			/* Message */ TEXT("NORMAL ") 
					);
			}
		}

	
		
		Position += Forward * DeltaTime * Speed;

		SetActorLocation(Position);
	}
}

void ASnakeBodyPart::SetNextPosition(const FVector& InPosition)
{
	if (IsValid(ChildBodyPart))
	{
		ChildBodyPart->SetNextPosition(NextPosition);
	}

	NextPosition = InPosition;
}

FVector ASnakeBodyPart::GetOffset()
{
	if (!IsValid(SnakePawn))
	{
		UE_LOG(LogTemp, Error, TEXT("SnakePawn is null in GetOffset!"));
		return FVector::ZeroVector;
	}

	if (GEngine)
	{
		FString OffsetMessage = FString::Printf(TEXT("GET OFFSET: %d"), static_cast<int32>(SnakePawn->Direction));
		GEngine->AddOnScreenDebugMessage(
			/* Key */ -1,
			/* TimeToDisplay */ 5.0f,
			/* Color */ FColor::Green,
			/* Message */ OffsetMessage
		);
	}

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

void ASnakeBodyPart::AddChildBodyPart(ASnakeBodyPart* InChildBodyPart, ASnakePawn* TempSnakePawn, int index)
{
	if(index == 1)
	{
		SnakePawn = TempSnakePawn;
	}
	
	if (IsValid(ChildBodyPart))
	{
		ChildBodyPart->AddChildBodyPart(InChildBodyPart,SnakePawn, 1);
		ChildBodyPart->intOffset += 100;
	}
	else
	{
	
		ChildBodyPart = InChildBodyPart;

		ChildBodyPart->SetActorLocation(GetActorLocation());
	}
}


