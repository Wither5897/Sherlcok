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
	UFUNCTION()
	void OnMyBtn_Back();
	// =================================Main=====================================
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Main_Btn_Character;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Main_Btn_Evidence;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Main_Btn_Weapon;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Main_Btn_Place;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Main_Btn_Back;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Main_Btn_PrePage;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Main_Btn_NextPage;
	UFUNCTION()
	void OnMyMain_Btn_Character();
	UFUNCTION()
	void OnMyMain_Btn_Evidence();
	UFUNCTION()
	void OnMyMain_Btn_Weapon();
	UFUNCTION()
	void OnMyMain_Btn_Place();
	UFUNCTION()
	void OnMyMain_Btn_Back();
	UFUNCTION()
	void OnMyMain_Btn_PrePage();
	UFUNCTION()
	void OnMyMain_Btn_NextPage();

	// =============================================Character================================
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Character_Btn_Back;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Btn_Character_0;
	UPROPERTY(EditDefaultsOnly, Category = "CharacterFactory")
	TSubclassOf<class AActor> Character_0Factory;
	UFUNCTION()
	void OnMyBtn_Character_0();
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Btn_Character_1;
	UPROPERTY(EditDefaultsOnly, Category = "CharacterFactory")
	TSubclassOf<class AActor> Character_1Factory;
	UFUNCTION()
	void OnMyBtn_Character_1();
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Btn_Character_2;
	UPROPERTY(EditDefaultsOnly, Category = "CharacterFactory")
	TSubclassOf<class AActor> Character_2Factory;
	UFUNCTION()
	void OnMyBtn_Character_2();

	// ==========================================Evidence======================================
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Evidence_Btn_Back;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Btn_Evidence_0;
	UPROPERTY(EditDefaultsOnly, Category = "EvidenceFactory")
	TSubclassOf<class AActor> EvidenceFactory_0;
	UPROPERTY(EditDefaultsOnly, Category = "EvidenceFactory")
	TSubclassOf<class AActor> EditorEvidenceFactory_0;
	UFUNCTION()
	void OnMyBtn_Evidence_0();


	// ============================================Weapon=====================================
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Weapon_Btn_Back;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Btn_Weapon_1;
	UPROPERTY(EditDefaultsOnly, Category = "WeaponFactory")
	TSubclassOf<class AActor> weaponFactory_1;
	UPROPERTY(EditDefaultsOnly, Category = "WeaponFactory")
	TSubclassOf<class AActor> EditorWeaponFactory_1;
	UFUNCTION()
	void OnMyBtn_Weapon_1();

	//===========================================Place======================================
	//////////////////////////////////////////////Up////////////////////////////////
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Place_Btn_Back;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Place_Btn_Furnitures_Up_0;
	UFUNCTION()
	void OnMyPlace_Btn_Furnitures_Up_0();
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Place_Btn_Furnitures_Up_1;
	UFUNCTION()
	void OnMyPlace_Btn_Furnitures_Up_1();
	//////////////////////////////////////////////Down////////////////////////////////////////
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Place_Btn_Furnitures_Down_0;
	UFUNCTION()
	void OnMyPlace_Btn_Furnitures_Down_0();
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Place_Btn_Furnitures_Down_1;
	UFUNCTION()
	void OnMyPlace_Btn_Furnitures_Down_1();
	//////////////////////////////////////Place_Vertical///////////////////////////////////////
	//////////////////////////////////////Place_Vertical_0////////////////////////////////////
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UVerticalBox* Place_Vertical_0;
	//////////////////////////////////////Place_Vertical_1//////////////////////////////////
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UVerticalBox* Place_Vertical_1;

	//====================================Place_Footway======================================
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Place_Btn_Footway_1;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Place_Btn_Footway_2;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Place_Btn_Footway_3;
	UPROPERTY(EditDefaultsOnly, Category = "Footway")
	TSubclassOf<class AActor> EditFootway_1Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Footway")
	TSubclassOf<class AActor> Footway_1Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Footway")
	TSubclassOf<class AActor> EditFootway_2Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Footway")
	TSubclassOf<class AActor> Footway_2Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Footway")
	TSubclassOf<class AActor> EditFootway_3Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Footway")
	TSubclassOf<class AActor> Footway_3Factory;
	UFUNCTION()
	void OnMyPlace_Btn_Footway_1();
	UFUNCTION()
	void OnMyPlace_Btn_Footway_2();
	UFUNCTION()
	void OnMyPlace_Btn_Footway_3();

	//========================================Place_Road===================================
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Place_Btn_Road_1;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Place_Btn_Road_2;
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Place_Btn_Road_3;
	UPROPERTY(EditDefaultsOnly, Category = "Place_Road")
	TSubclassOf<class AActor> EditRoad_1Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Place_Road")
	TSubclassOf<class AActor> Road_1Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Place_Road")
	TSubclassOf<class AActor> EditRoad_2Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Place_Road")
	TSubclassOf<class AActor> Road_2Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Place_Road")
	TSubclassOf<class AActor> EditRoad_3Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Place_Road")
	TSubclassOf<class AActor> Road_3Factory;
	UFUNCTION()
	void OnMyPlace_Btn_Road_1();
	UFUNCTION()
	void OnMyPlace_Btn_Road_2();
	UFUNCTION()
	void OnMyPlace_Btn_Road_3();

	//======================================Place_Station=======================================
	UPROPERTY(BlueprintReadWrite, meta = ( BindWidget ))
	class UButton* Place_Btn_Station_1;
	UPROPERTY(EditDefaultsOnly, Category = "Place_Station")
	TSubclassOf<class AActor> EditStation_1Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Place_Station")
	TSubclassOf<class AActor> Station_1Factory;
	UFUNCTION()
	void OnMyPlace_Btn_Station_1();

	//=====================================Furnitures==========================================
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Back;
	////////////////////////////////Furnitures_Vertical//////////////////////////
	UPROPERTY(meta = ( BindWidget ))
	class UVerticalBox* Furnitures_Vertical;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Up;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Bed;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical")
	TSubclassOf<class AActor> EditBedFactory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical")
	TSubclassOf<class AActor> BedFactory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Carpet;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical")
	TSubclassOf<class AActor> EditCarpetFactory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical")
	TSubclassOf<class AActor> CarpetFactory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_sofa;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical")
	TSubclassOf<class AActor> EditsofaFactory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical")
	TSubclassOf<class AActor> sofaFactory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Ottoman;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical")
	TSubclassOf<class AActor> EditOttomanFactory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical")
	TSubclassOf<class AActor> OttomanFactory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Down;
	UFUNCTION()
	void OnMyFurnitures_Btn_Up();
	UFUNCTION()
	void OnMyFurnitures_Btn_Bed();
	UFUNCTION()
	void OnMyFurnitures_Btn_Carpet();
	UFUNCTION()
	void OnMyFurnitures_Btn_sofa();
	UFUNCTION()
	void OnMyFurnitures_Btn_Ottoman();
	UFUNCTION()
	void OnMyFurnitures_Btn_Down();
	////////////////////////////////Furnitures_Vertical_1//////////////////////////
	UPROPERTY(meta = ( BindWidget ))
	class UVerticalBox* Furnitures_Vertical_1;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Up_1;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Chair_1;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_1")
	TSubclassOf<class AActor> EditChair_1Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_1")
	TSubclassOf<class AActor> Chair_1Factory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Chair_2;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_1")
	TSubclassOf<class AActor> EditChair_2Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_1")
	TSubclassOf<class AActor> Chair_2Factory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Chair_3;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_1")
	TSubclassOf<class AActor> EditChair_3Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_1")
	TSubclassOf<class AActor> Chair_3Factory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Chair_4;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_1")
	TSubclassOf<class AActor> EditChair_4Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_1")
	TSubclassOf<class AActor> Chair_4Factory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Down_1;
	UFUNCTION()
	void OnMyFurnitures_Btn_Up_1();
	UFUNCTION()
	void OnMyFurnitures_Btn_Chair_1();
	UFUNCTION()
	void OnMyFurnitures_Btn_Chair_2();
	UFUNCTION()
	void OnMyFurnitures_Btn_Chair_3();
	UFUNCTION()
	void OnMyFurnitures_Btn_Chair_4();
	UFUNCTION()
	void OnMyFurnitures_Btn_Down_1();
	////////////////////////////////Furnitures_Vertical_2//////////////////////////
	UPROPERTY(meta = ( BindWidget ))
	class UVerticalBox* Furnitures_Vertical_2;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Up_2;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Table_1;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_2")
	TSubclassOf<class AActor> EditTable_1Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_2")
	TSubclassOf<class AActor> Table_1Factory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Table_2;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_2")
	TSubclassOf<class AActor> EditTable_2Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_2")
	TSubclassOf<class AActor> Table_2Factory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Table_3;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_2")
	TSubclassOf<class AActor> EditTable_3Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_2")
	TSubclassOf<class AActor> Table_3Factory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Table_4;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_2")
	TSubclassOf<class AActor> EditTable_4Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_2")
	TSubclassOf<class AActor> Table_4Factory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Down_2;
	UFUNCTION()
	void OnMyFurnitures_Btn_Up_2();
	UFUNCTION()
	void OnMyFurnitures_Btn_Table_1();
	UFUNCTION()
	void OnMyFurnitures_Btn_Table_2();
	UFUNCTION()
	void OnMyFurnitures_Btn_Table_3();
	UFUNCTION()
	void OnMyFurnitures_Btn_Table_4();
	UFUNCTION()
	void OnMyFurnitures_Btn_Down_2();
	////////////////////////////////Furnitures_Vertical_3//////////////////////////
	UPROPERTY(meta = ( BindWidget ))
	class UVerticalBox* Furnitures_Vertical_3;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Up_3;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Tv;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_3")
	TSubclassOf<class AActor> EditTVFactory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_3")
	TSubclassOf<class AActor> TVFactory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Vase_1;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_3")
	TSubclassOf<class AActor> EditVase_1Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_3")
	TSubclassOf<class AActor> Vase_1Factory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Vase_2;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_3")
	TSubclassOf<class AActor> EditVase_2Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_3")
	TSubclassOf<class AActor> Vase_2Factory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Vase_3;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_3")
	TSubclassOf<class AActor> EditVase_3Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_3")
	TSubclassOf<class AActor> Vase_3Factory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Down_3;
	UFUNCTION()
	void OnMyFurnitures_Btn_Up_3();
	UFUNCTION()
	void OnMyFurnitures_Btn_Tv();
	UFUNCTION()
	void OnMyFurnitures_Btn_Vase_1();
	UFUNCTION()
	void OnMyFurnitures_Btn_Vase_2();
	UFUNCTION()
	void OnMyFurnitures_Btn_Vase_3();
	UFUNCTION()
	void OnMyFurnitures_Btn_Down_3();
	////////////////////////////////Furnitures_Vertical_4//////////////////////////
	UPROPERTY(meta = ( BindWidget ))
	class UVerticalBox* Furnitures_Vertical_4;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Up_4;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Vase_4;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_4")
	TSubclassOf<class AActor> EditVase_4Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_4")
	TSubclassOf<class AActor> Vase_4Factory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Vase_5;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_4")
	TSubclassOf<class AActor> EditVase_5Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_4")
	TSubclassOf<class AActor> Vase_5Factory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Vase_6;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_4")
	TSubclassOf<class AActor> EditVase_6Factory;
	UPROPERTY(EditDefaultsOnly, Category = "Furnitures_Vertical_4")
	TSubclassOf<class AActor> Vase_6Factory;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Vase_7;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Furnitures_Btn_Down_4;
	UFUNCTION()
	void OnMyFurnitures_Btn_Up_4();
	UFUNCTION()
	void OnMyFurnitures_Btn_Vase_4();
	UFUNCTION()
	void OnMyFurnitures_Btn_Vase_5();
	UFUNCTION()
	void OnMyFurnitures_Btn_Vase_6();
	UFUNCTION()
	void OnMyFurnitures_Btn_Vase_7();
	UFUNCTION()
	void OnMyFurnitures_Btn_Down_4();

	// =============================================SaveIntro & Outro Begin================================
	UPROPERTY(meta = ( BindWidget ))
	UButton* SaveTitleButton;
	UFUNCTION()
	void SaveTitleButtonClicked();
	
	UPROPERTY(meta = ( BindWidget ))
	UButton* SaveContextButton;
	UFUNCTION()
	void SaveContextButtonClicked();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> SaveIntroUIFactory;
	UPROPERTY()
	class UUW_EditIntro* SaveIntroUI;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> SaveOutroUIFactory;
	UPROPERTY()
	class UUW_EditOutro* SaveOutroUI;
	
	// =============================================SaveIntro & Outro End================================
	
	UPROPERTY()
	class APlayerController* pc;
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
