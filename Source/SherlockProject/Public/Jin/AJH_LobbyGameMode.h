// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AJH_LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API AAJH_LobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,Category="Mysettings")
	TSubclassOf<class UUserWidget> LoginWidget;	

	UPROPERTY(EditDefaultsOnly, Category="Mysettings")
	class UTJ_LoginWidget* LoginUI;

};
