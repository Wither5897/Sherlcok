// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Interaction.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UUW_Interaction : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;


	UPROPERTY(meta = (BindWidget))
	class UTextBlock* interact;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FString> interactArr;
};
