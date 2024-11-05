// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AJH_EditorToolWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UAJH_EditorToolWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = ( BindWidget ))
	class UWidgetSwitcher* EditorWidgetSwitcher;
	// Main
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Main_Btn_Character;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Main_Btn_Back;
	UFUNCTION()
	void OnMyMain_Btn_Character();
	UFUNCTION()
	void OnMyMain_Btn_Back();

	// Character
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Btn_Character_1;
	UFUNCTION()
	void OnMyBtn_Character_1();
	


	//// 뒤로가기 버튼 이벤트 (스택 활용)
	//UPROPERTY()
	//int32 currentPageIndex; // 현재 페이지
	//UPROPERTY()
	//int32 MemoriesPageIndex; // 기억할 페이지
	//UPROPERTY()
	//TArray<int32> PageHistory;

	
};
