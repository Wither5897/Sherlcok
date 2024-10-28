// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AJH_SummaryWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UAJH_SummaryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	class UButton* Btn_Click;
	UPROPERTY(meta=(BindWidget))
	class UImage* Img_Inven;

	UPROPERTY(EditDefaultsOnly)
	class UInventoryWidget* InventoryUI;

	UFUNCTION()
	void OnMyBtn_Click();

};
