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
	class UButton* Btn_Back;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UButton* Btn_FirstCrimeTravel;
	UPROPERTY(VisibleAnywhere, meta = ( BindWidget ), Category = "MySettings")
	class UButton* Btn_LevelBack;


	UPROPERTY(EditDefaultsOnly, meta = ( BindWidget ), Category = "MySettings")
	class UWidgetSwitcher* Switcherindex;
	UPROPERTY(BlueprintReadOnly)
	class UAJH_SherlockGameInstance* gi;

	UFUNCTION()
	void OnMyBtn_Crimefirst();
	UFUNCTION()
	void OnMyBtn_Back();
	UFUNCTION()
	void OnMyBtn_FirstCrimeTravel();
	UFUNCTION()
	void OnMyBtn_LevelBack();

};
