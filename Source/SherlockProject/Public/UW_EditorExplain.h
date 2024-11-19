// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_EditorExplain.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UUW_EditorExplain : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY()
	class AAJH_EditorCharacter* player;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExplainSave;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExplainDelete;
	UFUNCTION()
	void OnMyExplainDelete();
	UPROPERTY()
	class UAJH_ExPlainBtnWidget* ExPlainBtnWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ExPlainBtnFactory;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> WorldActorFactory;
	UPROPERTY()
	class AAJH_WorldActor* WorldActor;
	
};
