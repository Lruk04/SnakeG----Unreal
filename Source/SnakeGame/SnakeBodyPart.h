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
private:
	

<<<<<<< HEAD
	
public:

	
=======

	ASnakePawn* SnakePawn = nullptr;
public:

	int intOffset;

	FVector GetOffset();
>>>>>>> c07a0f259513bb480206b473059b372bcfec839a
	// Sets default values for this actor's properties
	ASnakeBodyPart();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	// Our snake collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* CollisionComponent;

<<<<<<< HEAD
	void AddChildBodyPart(ASnakeBodyPart* InChildBodyPart);
=======
	void AddChildBodyPart(ASnakeBodyPart* InChildBodyPart, ASnakePawn* TempSnakePawn);
>>>>>>> c07a0f259513bb480206b473059b372bcfec839a

	
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
