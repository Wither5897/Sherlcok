// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LightWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API ULightWidget : public UUserWidget
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
	class UAJH_SherlockGameInstance* gi;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class AAJH_Sun* SunActor;
	UPROPERTY(EditDefaultsOnly)
	FLinearColor sunColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "-1.0", ClampMax = "1.0", SliderMin = "-1.0", SliderMax = "1.0"))
	float SKSunHeight;
};

