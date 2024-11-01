// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AJH_LoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UAJH_LoginWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

public:
	
    UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MySettings")
	class UEditableText* Edit_hostName;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MySettings")
	class UButton* Btn_findSessions;

    UPROPERTY(EditDefaultsOnly, meta = (BindWidget), BlueprintReadWrite, Category = "MySettings")
	class UWidgetSwitcher* Switcher_Opening;

	UPROPERTY(BlueprintReadOnly)
	class UAJH_SherlockGameInstance* gi;

	//UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MySettings")
	//class UButton* ResetButton;
	
	UFUNCTION()
	void OnClickedFindSessionsButton();
	UFUNCTION()
	void OnClickedResetButton();
	UFUNCTION()
	void OnMyTextChanged(const FText& InText);
	
};
