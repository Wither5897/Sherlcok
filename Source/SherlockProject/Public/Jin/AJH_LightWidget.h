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
	UPROPERTY()
	class AAJH_Sun* HeightSun;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AAJH_Sun> HeightSunFactory;

	UPROPERTY()
	class AActor* SunActor;
};
