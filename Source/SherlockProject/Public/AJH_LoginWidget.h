// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AJH_LoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UAJH_LoginWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	class UButton* CR_Btn_CreateRoom;
	UPROPERTY(meta=(BindWidget))
	class UEditableText* CR_Edit_RoomName;

	UFUNCTION()
	void CR_OnClickCreateRoom();
	
};
