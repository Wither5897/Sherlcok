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
	
	void SetPlayerIdNum(int32 newPlayerID);

	UFUNCTION(BlueprintCallable, Category = "MultiPlayerState")
	int32 GetPlayerIdNum() const { return PlayerIDNum; }

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_PlayerIDNum();
	
private:
	UPROPERTY(ReplicatedUsing = OnRep_PlayerIDNum)
	int32 PlayerIDNum;
};
