// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_SingleReport.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UUW_SingleReport : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = ( BindWidget ))
	class UTextBlock* sub;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FString> subString;

	UPROPERTY(BlueprintReadOnly, meta = ( BindWidget ))
	class UTextBlock* percent;

	UPROPERTY(BlueprintReadOnly, meta = ( BindWidget ))
	class UTextBlock* EndingMarkShadow;

	UPROPERTY(BlueprintReadOnly, meta = ( BindWidget ))
	class UTextBlock* EndingMark;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FString> EndingMarkShadowArr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FString> EndingMarkArr;

	UPROPERTY()
	class ATP_ThirdPersonCharacter* me;
	
};
