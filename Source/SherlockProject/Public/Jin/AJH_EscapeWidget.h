// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AJH_EscapeWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UAJH_EscapeWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Escape_Btn_Yes;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Escape_Btn_No;

	UFUNCTION()
	void OnMyEscape_Btn_Yes();
	UFUNCTION()
	void OnMyEscape_Btn_No();

	UPROPERTY(BlueprintReadOnly)
	class UAJH_SherlockGameInstance* gi;
	UPROPERTY()
	class APlayerController* pc;
	UPROPERTY()
	class AAJH_EditorCharacter* me;
};
