// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_EditorExplain.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UUW_EditorExplain : public UUserWidget
{
	GENERATED_BODY()


	UPROPERTY(meta = (BindWidget))
	class UButton* ExplainSave;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExplainDelete;
	
};
