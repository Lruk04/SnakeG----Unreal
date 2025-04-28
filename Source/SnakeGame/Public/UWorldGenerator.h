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

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};