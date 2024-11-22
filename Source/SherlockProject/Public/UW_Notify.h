// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Animation/WidgetAnimation.h"
#include "UW_Notify.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UUW_Notify : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UPROPERTY()
	class ATP_ThirdPersonCharacter* me;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* category;

	UPROPERTY(meta = (BindWidget))
	class UImage* category_Image;

	UPROPERTY(EditDefaultsOnly)
	TArray<class UTexture2D*> categoryImgArr;

	void notifySetting(int32 value);

	UPROPERTY(EditDefaultsOnly, meta = ( BindWidgetAnim), Transient, Category = MySettings)
	class UWidgetAnimation* Notifyinfo;

	void PlayNotifyAnim();


	void PlayPoliceSoundWithDelay();
	void PlayCallSoundWithDelay();

	FTimerHandle PlaySoundTimerHandle;

};
