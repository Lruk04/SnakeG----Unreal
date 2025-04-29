// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PersistentGameDataSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEGAME_API UPersistentGameDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ScoreData")
	int Score = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ScoreData")
	int HighScore = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OptionData")
	bool TwoPlayerCoOp = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OptionData")
	bool AgainstAi = false;
	

	UFUNCTION(BlueprintCallable, Category = "ScoreData")
	void SetScore(int NewScore);

	UFUNCTION(BlueprintCallable, Category = "ScoreData")
	void SetHighScore(int NewHighScore);
	
	UFUNCTION(BlueprintCallable, Category = "ScoreData")
	void AddScore(int NewScore);

	UFUNCTION(BlueprintCallable, Category = "ScoreData")
	void DeductScore(int NewScore);


	UFUNCTION(BlueprintCallable, Category = "OptionData")
	void SetTwoPlayerCoOp(bool NewTwoPlayerCoOp);

	UFUNCTION(BlueprintCallable, Category = "OptionData")
	void SetAgainstAi(bool NewAgainstAi);

	
	
private:
	
};
