// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AJH_CreatorToolTravel.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UAJH_CreatorToolTravel : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY()
	class ATP_ThirdPersonCharacter* player;
	UPROPERTY()
	class ASherlockPlayerController* pc;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Btn_Travel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Btn_Cancel;

	UFUNCTION()
	void OnMyBtn_Travel();
	UFUNCTION()
	void OnMyBtn_Cancel();
	
};
