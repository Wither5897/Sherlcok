// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AJH_EditerToolGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API AAJH_EditerToolGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAJH_EditerToolGameMode();

protected:
	virtual void BeginPlay() override;

public:
	/*UFUNCTION(Category = "Editor Tool")
	void WorldActorLocation(const FVector& NewLocation);*/

	UPROPERTY()
	class AAJH_EditorCharacter* player;
	UPROPERTY()
	class AAJH_EditorPlayerController* pc;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class APawn> playerFactory;

};
