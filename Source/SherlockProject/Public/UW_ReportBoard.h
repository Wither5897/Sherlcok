﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanel.h"
#include "SK/ItemWidget.h"
#include "UW_ReportBoard.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UUW_ReportBoard : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	/*UPROPERTY()
	class UItemWidget* itemwidget;*/

	//TArray<bool> check;
	
	//void CheckMyNumberConditions();
	
	
	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* OpenReportButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* OpenReportButton_1;

	UPROPERTY(meta = (BindWidget))
	class UButton* OpenReportButton_2;

	UPROPERTY(meta = (BindWidget))
	class UButton* OpenReportButton_3;

	UPROPERTY(meta = ( BindWidget ))
	class UBackgroundBlur* BackgroundBlur_1;

	UPROPERTY(EditDefaultsOnly, meta = ( BindWidget ))
	class UWidgetSwitcher* WidgetSwitcher_1;


	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_138;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_1;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_2;

	UFUNCTION()
	void OpenEvidence1();

	UFUNCTION()
	void OpenEvidence2();

	UFUNCTION()
	void OpenEvidence3();

	UFUNCTION()
	void OpenEvidence();

	UFUNCTION()
	void CloseButtonClicked();
};
