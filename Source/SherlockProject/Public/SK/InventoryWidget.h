// Fill out your copyright notice in the Description page of Project Settings.

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

	UPROPERTY()
	class UTexture2D* SavedTexture;

	UPROPERTY()
	class UTexture2D* InitTexture;

	UPROPERTY(meta = (BindWidget))
	class UButton* ResetButton;
	UFUNCTION()
	void ResetButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UMultiLineEditableText* SuspectTextField;

	UPROPERTY(meta = (BindWidget))
	class UMultiLineEditableText* WeaponTextField;

	UPROPERTY(meta = (BindWidget))
	class UMultiLineEditableText* MainEvidenceTextField;

	UPROPERTY(meta = (BindWidget))
	class UMultiLineEditableText* SpecialThingTextField;

	bool bIsDoubleClick = false;

	void InitDoubleClick();

	void DoubleClick(class UMultiLineEditableText* textbox);

	UPROPERTY(meta = (BindWidget))
	class UImage* SuspectImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* WeaponImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* MainEvidenceImage;

	UPROPERTY(meta = ( BindWidget ))
	class UImage* SpecialThingImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<class UItemWidget*> ItemArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<class UNoteItemWidget*> NoteItemArray;


};
