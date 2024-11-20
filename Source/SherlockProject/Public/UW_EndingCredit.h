// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_EndingCredit.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UUW_EndingCredit : public UUserWidget
{
	GENERATED_BODY()



public:

	virtual void NativeConstruct() override;

	UPROPERTY()
	class ATP_ThirdPersonCharacter* me;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Job;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SubExplain;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* sub;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* percent;

	UPROPERTY(meta = (BindWidget))
	class UImage* jobImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<class UTexture2D*> jobImageTexture;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FString> jobString;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FString> subString;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FString> SubExplainString;
};
