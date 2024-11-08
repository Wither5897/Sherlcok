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
	AMultiPlayerState();
	
	void SetPlayerId(int32 newPlayerID);
	int32 GetPlayerId() const { return PlayerIDNum; }

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	UPROPERTY(Replicated)
	int32 PlayerIDNum;
};
