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

	UPROPERTY()
	class UDescriptionWidget* DescriptionUI;

	UPROPERTY(Meta = (BindWidget))
	class UImage* QuestionMark;

	UPROPERTY(Meta = ( BindWidget ))
	class UImage* Evidence;

};
