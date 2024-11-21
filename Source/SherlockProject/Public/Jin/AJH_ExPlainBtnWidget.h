// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AJH_ExPlainBtnWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UAJH_ExPlainBtnWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY()
	class AAJH_EditorCharacter* player;
	UPROPERTY()
	class APlayerController* pc;

	UPROPERTY(meta =(BindWidget))
	class UButton* Btn_ExPlain;
	UPROPERTY()
	class UUW_EditorExplain* EditorExplain;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> EditorExplainFactory;
	UFUNCTION()
	void OnMyBtn_ExPlain();
	UFUNCTION()
	void OnEnableBtn_ExPlain(bool bIsEnable);

	UPROPERTY(meta =(BindWidget))
	class UButton* Btn_InteractObj;
	UPROPERTY(meta =(BindWidget))
	class UButton* Btn_InteractObj_Cancel;
	UFUNCTION()
	void OnMyBtn_InteractObj();
	UFUNCTION()
	void OnMyBtn_InteractObj_Cancel();

	bool bIsPlainWidget;
};
