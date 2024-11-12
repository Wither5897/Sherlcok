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
	class UButton* Main_Btn_Weapon;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Main_Btn_Place;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Main_Btn_Back;
	UFUNCTION()
	void OnMyMain_Btn_Character();
	UFUNCTION()
	void OnMyMain_Btn_Weapon();
	UFUNCTION()
	void OnMyMain_Btn_Place();
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

	// Weapon
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Btn_Weapon_1;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Weapon_Btn_Back;
	
	UFUNCTION()
	void OnMyBtn_Weapon_1();

	//Place_Furnitures
	// Up
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Place_Btn_Furnitures_Up_0;
	UFUNCTION()
	void OnMyPlace_Btn_Furnitures_Up_0();
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Place_Btn_Furnitures_Up_1;
	UFUNCTION()
	void OnMyPlace_Btn_Furnitures_Up_1();
	// Down
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Place_Btn_Furnitures_Down_0;
	UFUNCTION()
	void OnMyPlace_Btn_Furnitures_Down_0();
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Place_Btn_Furnitures_Down_1;
	UFUNCTION()
	void OnMyPlace_Btn_Furnitures_Down_1();
	// Place_Vertical
	// Place_Vertical_0
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UVerticalBox* Place_Vertical_0;
	// Place_Vertical_1
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UVerticalBox* Place_Vertical_1;

	
	UPROPERTY()
	APlayerController* pc;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AAJH_EditorActor> EditorActorFactory;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> WorldActorFactory;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AAJH_WorldActor> weaponFactory_1;
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
