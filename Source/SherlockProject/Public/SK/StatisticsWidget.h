// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "StatisticsWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UStatisticsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnVisibilityChange(ESlateVisibility InVisibility);

	void UpdateStatistics();
	
	UPROPERTY()
	class ATP_ThirdPersonCharacter* me;

	int32 CalcSuspectRank();
	
	UPROPERTY(meta = (BindWidget))
	class UImage* SuspectTop1;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SuspectTextTop1;

	UPROPERTY(meta = (BindWidget))
	UImage* SuspectTop2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SuspectTextTop2;

	UPROPERTY(meta = (BindWidget))
	UImage* SuspectTop3;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SuspectTextTop3;

	void CalcWeaponRank();
	
	UPROPERTY(meta = (BindWidget))
	UImage* WeaponTop1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeaponTextTop1;

	UPROPERTY(meta = (BindWidget))
	UImage* WeaponTop2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeaponTextTop2;

	UPROPERTY(meta = (BindWidget))
	UImage* WeaponTop3;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeaponTextTop3;

	void CalcMainEviRank();
	
	UPROPERTY(meta = (BindWidget))
	UImage* MainEviTop1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MainEviTextTop1;

	UPROPERTY(meta = (BindWidget))
	UImage* MainEviTop2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MainEviTextTop2;

	UPROPERTY(meta = (BindWidget))
	UImage* MainEviTop3;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MainEviTextTop3;

	void CalcSpecialRank();
	
	UPROPERTY(meta = (BindWidget))
	UImage* SpecialTop1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SpecialTextTop1;

	UPROPERTY(meta = (BindWidget))
	UImage* SpecialTop2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SpecialTextTop2;

	UPROPERTY(meta = (BindWidget))
	UImage* SpecialTop3;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SpecialTextTop3;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;

	UFUNCTION()
	void OnClickedExit();

	UFUNCTION()
	void ServerTravelDelay();
};
