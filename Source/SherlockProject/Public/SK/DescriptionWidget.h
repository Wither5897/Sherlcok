// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DescriptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UDescriptionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Description1;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Description2;

	UPROPERTY(meta = ( BindWidget ))
	class UTextBlock* Description3;

	UFUNCTION(BlueprintCallable)
	void WhenItemClicked(int32 value);
	
	UFUNCTION(BlueprintCallable)
	void SetDescriptionText(FText Text1, FText Text2, FText Text3);

	void SetUIVisibility();

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;
	UFUNCTION()
	void BackButtonClicked();

	UPROPERTY(EditDefaultsOnly)
	TArray<class UTexture2D*> RealEvidenceArray;
	UPROPERTY(meta = (BindWidget))
	class UImage* RealEvidence;

	UPROPERTY(EditDefaultsOnly)
	TArray<class UTexture2D*> UnrealEvidenceArray;
	UPROPERTY(meta = (BindWidget))
	class UImage* UnrealEvidence;
};
