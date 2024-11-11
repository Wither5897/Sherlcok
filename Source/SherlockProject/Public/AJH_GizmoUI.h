// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AJH_GizmoUI.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UAJH_GizmoUI : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta=(bindWidget))
	class UWidgetSwitcher* Switcher_GizmoUI;
	UPROPERTY(EditDefaultsOnly, meta=(bindWidget))
	class UEditableText* Edit_Location_X;
	UPROPERTY(EditDefaultsOnly, meta=(bindWidget))
	class UEditableText* Edit_Location_Y;
	UPROPERTY(EditDefaultsOnly, meta=(bindWidget))
	class UEditableText* Edit_Location_Z;

	void OnMyEdit_Location();
	void GetEdit_Location();

	FString Location_X;
	FString Location_Y;
	FString Location_Z;

	FVector actorLocation;

	UPROPERTY()
	class AAJH_EditorCharacter* player;

};
