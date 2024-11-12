// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomizingWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UCustomizingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* CoatLeftButton;
	UFUNCTION()
	void CoatLeftButtonClicked();
	
	UPROPERTY(meta = (BindWidget))
	class UButton* CoatRightButton;
	UFUNCTION()
	void CoatRightButtonClicked();
	
	UPROPERTY(meta = (BindWidget))
	class UButton* HatLeftButton;
	UFUNCTION()
	void HatLeftButtonClicked();
	
	UPROPERTY(meta = (BindWidget))
	class UButton* HatRightButton;
	UFUNCTION()
	void HatRightButtonClicked();
	
	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton;
	UFUNCTION()
	void PlayButtonClicked();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CustomizingWidget")
	int32 CoatIdx;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CustomizingWidget")
	int32 HatIdx;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CustomizingWidget")
	TArray<class UMaterial*> MaterialColor;

	UPROPERTY()
	class ACustomizingCharacter* me;
};
