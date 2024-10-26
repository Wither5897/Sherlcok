// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MultiPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API AMultiPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void SetPlayerId(int32 newPlayerId) { PlayerID = newPlayerId; }
	int32 GetPlayerId() const { return PlayerID; }

private:
	int32 PlayerID;
	
};
