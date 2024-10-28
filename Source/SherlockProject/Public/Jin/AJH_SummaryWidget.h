﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AJH_SummaryWidget.generated.h"

/**
 * 
 */

 class UImage;
 class UButton;

UCLASS()
class SHERLOCKPROJECT_API UAJH_SummaryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Submit;
	UPROPERTY(meta=(BindWidget))
	UImage* Img_Inven;

	UPROPERTY(meta=(BindWidget))
	UImage* Img_SuspectImage;
	UPROPERTY(meta=(BindWidget))
	UImage* Img_WeaponImage;
	UPROPERTY(meta=(BindWidget))
	UImage* Img_MainEvidenceImage;
	UPROPERTY(meta=(BindWidget))
	UImage* Img_SpecialThingImage;

	UFUNCTION()
	void OnSuspectImage(class UTexture2D* SavedTexture);
	UFUNCTION()
	void OnWeaponImage(class UTexture2D* SavedTexture);
	UFUNCTION()
	void OnMainEvidenceImage(class UTexture2D* SavedTexture);
	UFUNCTION()
	void OnSpecialThingImage(class UTexture2D* SavedTexture);


	UPROPERTY()
	class ATP_ThirdPersonCharacter* me;

	UPROPERTY(EditDefaultsOnly)
	class UInventoryWidget* InventoryUI;

	UFUNCTION()
	void OnMyBtn_Click();

};
