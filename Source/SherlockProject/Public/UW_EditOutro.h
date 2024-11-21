// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_EditOutro.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UUW_EditOutro : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly, meta = ( BindWidget ))
	class UMultiLineEditableText* EndingMessage;

	UPROPERTY(BlueprintReadOnly, meta = ( BindWidget ))
	class UButton* StorySave;

	UFUNCTION()
	void StorySaveButtonClicked();

	UPROPERTY()
	FText StoryText;
};
