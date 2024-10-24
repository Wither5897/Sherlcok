// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SherlockHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API ASherlockHUD : public AHUD
{
	GENERATED_BODY()

public:
	ASherlockHUD();
	virtual void BeginPlay() override;

public:
	TSharedPtr<class SWidget> GetChatInputTextObject();
	void AddChatMessage(const FString& Message);

private:
	TSubclassOf<class UUW_Main> MainUIClass;
	class UUW_Main* MainUIObject;

private:
	bool CheckUIObject();
	bool CreateUIObject();
};
