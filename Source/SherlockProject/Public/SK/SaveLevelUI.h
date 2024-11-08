// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveLevelUI.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API USaveLevelUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* LevelNameEdit;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* ConfirmButton;

	UFUNCTION()
	void ConfirmButtonClicked();
};
