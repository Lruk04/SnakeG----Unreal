#pragma once
#include "Grid.h"
#include "UWorldGenDataAsset.h"
#include "UWorldGenerator.generated.h"

UCLASS(Blueprintable)
class UWorldGenerator final : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AActor*> SpawnedActor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WorldGenerator")
	const UWorldGenDataAsset* WorldGenDataAsset;
	
	UGridSubsystem* GridSubsystem;
	
	UWorldGenerator();
	virtual ~UWorldGenerator() override;

	UFUNCTION(BlueprintCallable, Category = "WorldGenerator")
	void GenerateMap(const FString& FileName, const UWorldGenDataAsset* dataAsset) const;

	UFUNCTION(BlueprintCallable, Category = "WorldGenerator")
	void ClearMap() const;


	UFUNCTION(BlueprintCallable, Category = "WorldGenerator")
	void SetSubSystem();
	
	UFUNCTION(BlueprintCallable, Category = "WorldGenerator")
	void SpawnApple(const UWorldGenDataAsset* dataAsset) const;

	UFUNCTION(BlueprintCallable, Category = "WorldGenerator")
	void SetAssetData(const UWorldGenDataAsset* dataAsset);

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};