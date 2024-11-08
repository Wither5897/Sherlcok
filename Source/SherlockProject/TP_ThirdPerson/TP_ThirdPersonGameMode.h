// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TP_ThirdPersonGameMode.generated.h"

UCLASS(minimalapi)
class ATP_ThirdPersonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATP_ThirdPersonGameMode();

	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	
	int32 NumPlayers = 0;

	UFUNCTION(Server, Reliable)
	void ServerTravelToLevel(const FString& LevelName);

	UPROPERTY()
	int32 UserReady = 0;


	UFUNCTION()
	void OnMyReadyCount(int32 ReadyCount);
};



