// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UItemWidget : public UUserWidget
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

	UPROPERTY(meta = (BindWidget))
	class UImage* Player1Light;

	UPROPERTY(meta = (BindWidget))
	class UImage* Player2Light;

	UPROPERTY(meta = (BindWidget))
	class UImage* Player3Light;
};
