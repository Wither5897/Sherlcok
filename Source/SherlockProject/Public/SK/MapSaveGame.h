// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Templates/SubclassOf.h"
#include "MapSaveGame.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FActorSaveData{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	FName ActorName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	FVector Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	TSubclassOf<AActor> ActorClass;
};

UCLASS()
class SHERLOCKPROJECT_API UMapSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	TArray<FActorSaveData> SavedActors;

	TMap<FString, TArray<FActorSaveData>> DataList;
};
