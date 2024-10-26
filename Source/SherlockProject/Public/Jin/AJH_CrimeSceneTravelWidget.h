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
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UButton* Btn_Crimefirst;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UButton* Btn_CrimeSecond;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UButton* Btn_CrimeThird;
	// Btn_Back(뒤로가기)
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UButton* Btn_Back;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UButton* Btn_Back_0;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UButton* Btn_Back_1;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UButton* Btn_Back_2;
	// Btn_Travel(레벨 이동)
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UButton* Btn_FirstCrimeTravel;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UButton* Btn_FirstCrimeReady;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UButton* Btn_SecondCrimeTravel;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UButton* Btn_SecondCrimeReady;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UButton* Btn_ThirdCrimeTravel;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UButton* Btn_ThirdCrimeReady;
	//UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	//class UButton* Btn_LevelBack;


	UPROPERTY(EditDefaultsOnly, meta = ( BindWidget ), Category = "MySettings")
	class UWidgetSwitcher* Switcherindex;
	UPROPERTY(BlueprintReadOnly)
	class UAJH_SherlockGameInstance* gi;

	UPROPERTY()
	int32 currentPageIndex;
	UPROPERTY()
	int32 lastPageIndex;
	UPROPERTY()
	TArray<int32> PageHistory;

	UFUNCTION()
	void OnMyBtn_Crimefirst();
	UFUNCTION()
	void OnMyBtn_Back();
	UFUNCTION()
	void OnMyBtn_Ready();
	UFUNCTION()
	void OnMyBtn_FirstCrimeTravel();
	UFUNCTION()
	void OnMyBtn_LevelBack();

};
