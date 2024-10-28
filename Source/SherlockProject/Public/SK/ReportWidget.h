// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReportWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UReportWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = ( BindWidget ))
	class UCanvasPanel* CanvasPanel_19;

	UPROPERTY(meta = ( BindWidget ))
	class UButton* CloseReportButton;

	UFUNCTION()
	void CloseReportButtonClicked();
	
};
