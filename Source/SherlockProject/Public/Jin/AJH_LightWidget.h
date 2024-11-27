// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AJH_LightWidget.generated.h"


 
UCLASS()
class SHERLOCKPROJECT_API UAJH_LightWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_morning;
	UFUNCTION()
	void OnMyBtn_morning();
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_lunch;
	UFUNCTION()
	void OnMyBtn_lunch();
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Dinner;
	UFUNCTION()
	void OnMyBtn_Dinner();

	UPROPERTY()
	class AAJH_DirectionalLight* directionalLightActor;
	UPROPERTY()
	class AAJH_EditorCharacter* player;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class AAJH_Sun* MorningSun;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AAJH_Sun> MorningSunFactory;
	bool bIsMorningSun = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class AAJH_Sun* MiddaySun;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AAJH_Sun> MiddaySunFactory;
	bool bIsMiddaySun = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class AAJH_Sun* MidnightSun;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AAJH_Sun> MidnightSunFactory;
	bool bIsMidnightSun = false;

	UPROPERTY()
	class AAJH_Sun* SunActor;
	UPROPERTY(EditDefaultsOnly)
	FLinearColor sunColor;
};
