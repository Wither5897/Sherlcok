// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AJH_EditorToolWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UAJH_EditorToolWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UWidgetSwitcher* EditorWidgetSwitcher;
	// Main
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Main_Btn_Character;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Main_Btn_Back;
	UFUNCTION()
	void OnMyMain_Btn_Character();
	UFUNCTION()
	void OnMyMain_Btn_Back();

	// Character
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Btn_Character_1;
	UFUNCTION()
	void OnMyBtn_Character_1();
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Btn_Character_2;
	UFUNCTION()
	void OnMyBtn_Character_2();
	
	UPROPERTY()
	APlayerController* pc;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AAJH_EditorActor> EditorActorFactory;
	UPROPERTY()
	class AAJH_EditorActor* EditorActor;
	ETraceTypeQuery query;
	FHitResult outHit;
	UPROPERTY()
	class AAJH_EditorCharacter* me;
	bool bIsSpawn = false;

	// 스폰 (스택 활용)
	UPROPERTY()
	int32 currentActorIndex; // 현재 엑터
	UPROPERTY()
	int32 MemoriesActorIndex; // 기억할 엑터
	UPROPERTY()
	TMap<int32, TWeakObjectPtr<AAJH_EditorActor>> ActorMap;
	UPROPERTY()
	TArray<int32> ActorHistory;

	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	UButton* LevelSaveButton;

	UFUNCTION()
	void LevelSaveButtonClicked();
};
