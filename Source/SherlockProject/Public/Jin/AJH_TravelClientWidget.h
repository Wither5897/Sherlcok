// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AJH_TravelClientWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UAJH_TravelClientWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:

	UPROPERTY(meta=(BindWidget))
	class UButton* Btn_FirstCrimeReady;
	UPROPERTY(meta=(BindWidget))
	class UButton* Btn_Cancel;

	UFUNCTION()
	void OnMyBtn_FirstCrimeReady();
	UFUNCTION()
	void OnMyBtn_Cancel();

	UPROPERTY()
	class ASherlockPlayerController* SherlockPC;

};
