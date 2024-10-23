// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "AJH_UserNameWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UAJH_UserNameWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	void SetUserName(FString UserName);

};
