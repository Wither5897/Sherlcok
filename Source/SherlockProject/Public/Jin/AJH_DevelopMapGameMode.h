// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AJH_DevelopMapGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API AAJH_DevelopMapGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerTravelToLevel(const FString& LevelName);

};
