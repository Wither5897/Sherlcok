// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AJH_CrimeSceneTravelWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UAJH_CrimeSceneTravelWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	// Default Setting =========================================================
	UPROPERTY()
	class ATP_ThirdPersonCharacter* player;
	UPROPERTY()
	class ASherlockPlayerController* SherlockPC;
	UPROPERTY(BlueprintReadOnly)
	class UAJH_SherlockGameInstance* gi;
	UPROPERTY(BlueprintReadOnly)
	class ATP_ThirdPersonGameMode* gm;
	UPROPERTY(EditDefaultsOnly)
	class USoundBase* PaperscrollSound;

	UPROPERTY(BlueprintReadOnly)
	class UMapSaveGame* LoadGameInstance;
	
	UPROPERTY(EditDefaultsOnly, meta = ( BindWidget ), Category = "MySettings")
	class UWidgetSwitcher* Switcherindex;

	// =========================================================================
	
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UButton* Btn_Crimefirst;
	UFUNCTION()
	void OnMyBtn_Crimefirst();
	
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UButton* Btn_CrimeSecond;
	UFUNCTION()
	void OnMyBtn_CrimeSecond();
	
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UButton* Btn_CrimeThird;
	UFUNCTION()
	void OnMyBtn_CrimeThird();
	
	// Btn_Back(뒤로가기)
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UButton* Btn_Back;
	UFUNCTION()
	void OnMyBtn_Back();
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UButton* Btn_Back_0;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UButton* Btn_Back_1;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UButton* Btn_Back_2;
	UFUNCTION()
	void OnMyBtn_Back_1();
	
	// Ready
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UButton* Btn_FirstCrimeReady;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UButton* Btn_SecondCrimeReady;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UButton* Btn_ThirdCrimeReady;
	UFUNCTION()
	void OnMyBtn_Ready();

	// Cancel
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UButton* Btn_Cancel;
	UFUNCTION()
	void OnMyBtn_Cancel();

	// Btn_Travel(레벨 이동)
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UButton* Btn_FirstCrimeTravel;
	UFUNCTION()
	void OnMyBtn_FirstCrimeTravel();

	// Btn_Travel(레벨 이동)
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UButton* Btn_SecondCrimeTravel;
	UFUNCTION()
	void OnMyBtn_SecondCrimeTravel();

	// Btn_Travel(레벨 이동)
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UButton* Btn_ThirdCrimeTravel;
	UFUNCTION()
	void OnMyBtn_ThirdCrimeTravel();
	
	//UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	//class UButton* Btn_LevelBack;
	
	UFUNCTION()
	void OnMyBtn_LevelBack();
	
	// 사건 목록
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UImage* Img_CrimeImage_0;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UImage* Img_CrimeImage_1;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UImage* Img_CrimeImage_2;
	
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UTextBlock* Txt_CrimeName_0;
	FText CrimeName;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UTextBlock* Txt_CrimeName_1;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UTextBlock* Txt_CrimeName_2;

	UFUNCTION()
	void OnTextCrimeName();
	// 여고생 사건 UI
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UImage* Img_CrimeImage_0_0;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UImage* Img_CrimeImage_1_1;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	UImage* Img_CrimeImage_2_2;

	UPROPERTY(VisibleAnywhere, meta = ( BindWidgetAnim ), Transient, Category = "MySettings")
	UWidgetAnimation* Anim_Btn_Crimefirst;
	UFUNCTION()
	void OnMyAnim_Btn_CrimefirstHoVered();
	UFUNCTION()
	void OnMyAnim_Btn_CrimefirstUnHoVered();
	UPROPERTY(VisibleAnywhere, meta = ( BindWidgetAnim ), Transient, Category = "MySettings")
	UWidgetAnimation* Anim_Switcherindex;
	UFUNCTION()
	void OnMyAnim_Switcherindex();
	UPROPERTY(VisibleAnywhere, meta = ( BindWidgetAnim ), Transient, Category = "MySettings")
	UWidgetAnimation* Anim_Canvas_First;
	UFUNCTION()
	void OnMyAnim_Canvas_First();
	UPROPERTY(VisibleAnywhere, meta = ( BindWidgetAnim ), Transient, Category = "MySettings")
	UWidgetAnimation* Anim_Canvas_Second;
	UFUNCTION()
	void OnMyAnim_Canvas_Second();

	
	// 뒤로가기 버튼 이벤트 (스택 활용)
	UPROPERTY()
	int32 currentPageIndex;
	UPROPERTY()
	int32 lastPageIndex;
	UPROPERTY()
	TArray<int32> PageHistory;

	UFUNCTION()
	void RefreshList();
};
