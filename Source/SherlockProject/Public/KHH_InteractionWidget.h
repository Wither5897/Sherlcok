// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KHH_InteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UKHH_InteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	virtual void NativeConstruct() override;

	UPROPERTY(meta = ( Bindwidget));
	class UWidgetSwitcher* InteractionWidgetSwitcher;
	
};
