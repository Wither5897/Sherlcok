// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_EditIntro.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UUW_EditIntro : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, meta = ( BindWidget ))
	class UEditableText* TitleEditText;

	UPROPERTY(BlueprintReadOnly, meta = ( BindWidget ))
	class UMultiLineEditableText* SubTitleTextMulti;

	UPROPERTY(BlueprintReadOnly, meta = ( BindWidget ))
	class UButton* TitleSave;
};
