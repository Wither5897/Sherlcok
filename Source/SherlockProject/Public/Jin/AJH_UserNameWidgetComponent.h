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
	UAJH_UserNameWidgetComponent();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	UFUNCTION(Server, Reliable)
	void ServerSetUserName(const FString& UserName_);
	UFUNCTION(NetMulticast, Reliable)
	void MultiCastSetUserName(const FString& UserName_);

	UPROPERTY(ReplicatedUsing = OnRep_UserName, EditDefaultsOnly)
	FString UserName;
	UFUNCTION()
	void OnRep_UserName();

	class ASherlockPlayerController* pc;
	void CheckPlayerController();

	void SetUserName(FString UserName_);

};
