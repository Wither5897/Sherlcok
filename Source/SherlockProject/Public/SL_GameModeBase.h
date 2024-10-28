// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SL_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API ASL_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASL_GameModeBase();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerTravelToLevel(const FString& LevelName);

	UPROPERTY()
	int32 UserReady = 0;


	UFUNCTION()
	void OnMyReadyCount(int32 ReadyCount);
	
};
