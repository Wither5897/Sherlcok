﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DescriptionUIFactory; 

	UPROPERTY()
	class UDescriptionWidget* DescriptionUI;

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* EvidenceList1;

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* EvidenceList2;

	UPROPERTY(meta = (BindWidget))
	class UButton* PageDownButton;
	UFUNCTION()
	void PageDownButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* PageUpButton;
	UFUNCTION()
	void PageUpButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EvidencePage;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CaseRecordScreen;

	UPROPERTY(meta = (BindWidget))
	class UButton* ShowEvidenceButton;

	UFUNCTION()
	void ShowEvidenceButtonClicked();
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CaseGuessScreen;

	UPROPERTY(meta = (BindWidget))
	class UButton* ShowNoteButton;
	UFUNCTION()
	void ShowNoteButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* SuspectButton;
	UFUNCTION()
	void SuspectButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* WeaponButton;
	UFUNCTION()
	void WeaponButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* MainEvidenceButton;
	UFUNCTION()
	void MainEvidenceButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* SpecialThingButton;
	UFUNCTION()
	void SpecialThingButtonClicked();

	FLinearColor SavedTexture;

	UPROPERTY(meta = (BindWidget))
	class UButton* ResetButton;
	UFUNCTION()
	void ResetButtonClicked();

	FLinearColor InitColor;
};
