﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NoteItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UNoteItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	int32 GetMyNumber();

	UFUNCTION(BlueprintCallable)
	void WhenFindItem();

	UPROPERTY(Meta = (BindWidget))
	class UImage* QuestionMark;

	UPROPERTY(Meta = ( BindWidget ))
	class UImage* Evidence;

	UPROPERTY(Meta = ( BindWidget ))
	class UImage* HighlightImage;

	UPROPERTY(EditDefaultsOnly)
	TArray<class UTexture2D*> ItemColor;

	UPROPERTY()
	class UInventoryWidget* Inven;

	UPROPERTY()
	class UDescriptionWidget* DescriptionUI;

	UPROPERTY(meta = (BindWidget))
	class UButton* ItemButton;

	UFUNCTION()
	void ItemButtonClicked();

	UPROPERTY()
	class UTexture* SavedTexture;

	bool bIsDisabled = false;
	
	UFUNCTION()
	void DisableInteraction();

	UFUNCTION()
	void EnableInteraction();

	bool IsDisabled() const { return bIsDisabled; }
};
