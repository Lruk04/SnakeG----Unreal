// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Definitions.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "SnakePawn.generated.h"

class ASnakeBodyPart;
class ASnakePlayerState;

UCLASS()
class SNAKEGAME_API ASnakePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASnakePawn();

	// So that we can have multiple children connected to the root component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	// Our snake collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESnakeDirection Direction = ESnakeDirection::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASnakeBodyPart> BodyPartClass;

protected:
	UPROPERTY()
	ASnakePlayerState* SnakePlayerState = nullptr;

	// So that we can utilize gravity
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ToolTip = "Used for falling and jumping."))
	float VelocityZ = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ToolTip = "If the snake is in air."))
	bool bInAir = false;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ToolTip = "The forward rotation of the snake."))
	FRotator ForwardRotation;

	// Direction queue that gets set and poped each time the snake reaches a new tile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ESnakeDirection> DirectionQueue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ToolTip = "How long the snake has moved since reaching the last tile."))
	float MovedTileDistance = 0.0f;

	UPROPERTY()
	ASnakeBodyPart* ChildBodyPart = nullptr;

	UPROPERTY()
	int TmpMovementMade = 0;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Updates the direction each time a new tile is reached
	UFUNCTION()
	void UpdateDirection();

	// Updates snake movment (called from Tick)
	UFUNCTION()
	void UpdateMovement(float DeltaTime);

	// Move the snake in the set distance
	UFUNCTION()
	void MoveSnake(float Distance);

	// Updates falling (called from Tick)
	UFUNCTION()
	void UpdateFalling(float DeltaTime);

	// Updates falling (called from Tick)
	UFUNCTION()
	void AteApple();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the Pawn gets possessed by a controller
	virtual void PossessedBy(AController* NewController) override;

	// Blueprint callable Jump function
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Makes the snake jump."))
	void Jump();

	// Blueprint callable SetNextDirection function
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Add a direction onto a queue where the first in line direction gets set and poped."))
	void SetNextDirection(ESnakeDirection InDirection);
};
