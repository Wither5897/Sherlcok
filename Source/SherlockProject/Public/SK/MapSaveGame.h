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
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	FVector Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	FString String;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	bool boolean;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	TSubclassOf<AActor> ActorClass;


	FActorSaveData()
		: Location(FVector::ZeroVector),
		  Rotation(FRotator::ZeroRotator),
		  Scale(FVector(1.f, 1.f, 1.f)),
		  String(" "),
		  boolean(),
		  ActorClass(nullptr){
	}
};

USTRUCT(BlueprintType)
struct FLevelSaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	FString LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	FText IntroTitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	FText IntroContextText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	FText OutroText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	TArray<FActorSaveData> SavedActors;

	FLevelSaveData()
		: LevelName(TEXT(""))
	{}
};

UCLASS()
class SHERLOCKPROJECT_API UMapSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	TArray<FActorSaveData> SavedActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	TArray<FLevelSaveData> DataList;
};
