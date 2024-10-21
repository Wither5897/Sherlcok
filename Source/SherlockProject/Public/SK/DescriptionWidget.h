// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DescriptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UDescriptionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemDescription;

	UFUNCTION(BlueprintCallable)
	void WhenItemClicked(int32 value);
	
	UFUNCTION(BlueprintCallable)
	void SetDescriptionText(FText NewText);

	void SetUIVisibility();

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;
	UFUNCTION()
	void BackButtonClicked();
};
