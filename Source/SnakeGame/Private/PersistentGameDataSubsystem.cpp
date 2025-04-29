// Fill out your copyright notice in the Description page of Project Settings.


#include "PersistentGameDataSubsystem.h"



void UPersistentGameDataSubsystem::SetScore(int NewScore)
{
	Score = NewScore;
}

void UPersistentGameDataSubsystem::SetHighScore(int NewHighScore)
{
	HighScore = NewHighScore;
}

void UPersistentGameDataSubsystem::AddScore(int NewScore)
{
	Score += NewScore;
}

void UPersistentGameDataSubsystem::DeductScore(int NewScore)
{
	Score -= NewScore;
}


void UPersistentGameDataSubsystem::SetTwoPlayerCoOp(bool NewTwoPlayerCoOp)
{
	TwoPlayerCoOp = NewTwoPlayerCoOp;
}

void UPersistentGameDataSubsystem::SetAgainstAi(bool NewAgainstAi)
{
	AgainstAi = NewAgainstAi;
}