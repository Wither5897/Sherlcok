// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KHH_InteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UKHH_InteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Explain_1;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Explain_2;

	UPROPERTY(meta = ( BindWidget ))
	class UTextBlock* Explain_3;

	UPROPERTY(meta = ( BindWidget ))
	class UImage* ExplainImage;

	UPROPERTY(EditAnywhere)
	TArray<class UTexture2D*> ItemTexture;

	void WhenItemClick(int32 value);

	void SetExplainText(FText Text1, FText Text2, FText Text3);
};
