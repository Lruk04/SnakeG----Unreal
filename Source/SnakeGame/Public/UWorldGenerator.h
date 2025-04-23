#pragma once
#include "Grid.h"
#include "UWorldGeneratorDataAsset.h"
#include "UWorldGenerator.generated.h"

UCLASS(Blueprintable)
class UWorldGenerator final : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	
	
	Grid* GameGrid = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AActor*> SpawnedActor;


	
	UWorldGenerator();
	virtual ~UWorldGenerator() override;

	UFUNCTION(BlueprintCallable, Category = "WorldGenerator")
	void GenerateMap(const FString& FileName, UWorldGeneratorDataAsset* dataAsset) const;

	UFUNCTION(BlueprintCallable, Category = "WorldGenerator")
	void ClearMap() const;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};