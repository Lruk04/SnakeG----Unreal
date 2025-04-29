// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakePawn.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "SnakeBodyPart.generated.h"

class ASnakePlayerState;

UCLASS()
class SNAKEGAME_API ASnakeBodyPart : public AActor
{
	GENERATED_BODY()

	
public:

	
	
	// Sets default values for this actor's properties
	ASnakeBodyPart();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	// Our snake collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* CollisionComponent;

	void AddChildBodyPart(ASnakeBodyPart* InChildBodyPart);

	
protected:
	UPROPERTY()
	ASnakePlayerState* SnakePlayerState = nullptr;

	UPROPERTY()
	ASnakeBodyPart* ChildBodyPart = nullptr;

	UPROPERTY()
	FVector NextPosition = FVector::ZeroVector;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetNextPosition(const FVector& InPosition);

};
