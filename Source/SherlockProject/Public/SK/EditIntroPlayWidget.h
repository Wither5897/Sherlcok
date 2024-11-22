// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EditIntroPlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UEditIntroPlayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString IntroFullText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText IntroTitleText;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayStart();
};
