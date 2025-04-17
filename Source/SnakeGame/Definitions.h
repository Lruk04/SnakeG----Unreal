// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class ESnakeDirection : uint8
{
	Up = 0,
	Right = 1,
	Down = 2,
	Left = 3,
	None = 255
};

constexpr float TileSize = 100.0f;

constexpr float GWorld_Width = 72.0f;
constexpr float GWorld_Height = 48.0f;