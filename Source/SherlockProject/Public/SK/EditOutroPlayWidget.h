// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EditOutroPlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UEditOutroPlayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText OutroContext;
};
