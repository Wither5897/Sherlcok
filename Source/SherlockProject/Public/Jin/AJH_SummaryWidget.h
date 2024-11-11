// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "AJH_SummaryWidget.generated.h"

/**
 * 
 */

 class UImage;
 class UButton;

USTRUCT(BlueprintType)
struct FClueData{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ClueID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SuspectCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WeaponCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MainEvidenceCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SpecialThingCount;
};

UCLASS()
class SHERLOCKPROJECT_API UAJH_SummaryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Submit;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Img_SuspectImage1;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Img_SuspectImage2;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Img_SuspectImage3;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Img_WeaponImage1;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Img_WeaponImage2;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Img_WeaponImage3;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Img_MainEvidenceImage1;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Img_MainEvidenceImage2;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Img_MainEvidenceImage3;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Img_SpecialThingImage1;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Img_SpecialThingImage2;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Img_SpecialThingImage3;
	

	UFUNCTION()
	void OnSuspectImage(class UTexture2D* SavedTexture, int32 playerid);
	UFUNCTION()
	void OnWeaponImage(class UTexture2D* SavedTexture, int32 playerid);
	UFUNCTION()
	void OnMainEvidenceImage(class UTexture2D* SavedTexture, int32 playerid);
	UFUNCTION()
	void OnSpecialThingImage(class UTexture2D* SavedTexture, int32 playerid);


	UPROPERTY()
	class ATP_ThirdPersonCharacter* me;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInventoryWidget* InventoryUI;

	UFUNCTION()
	void OnMyBtn_Click();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* EvidenceDataTable;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<class UTexture2D*> AllTexture;

	TArray<FClueData> ClueDataArray;
	
	void LoadClueData();

	void SaveClueData();
};
