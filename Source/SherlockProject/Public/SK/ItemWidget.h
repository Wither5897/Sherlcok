// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "ItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	int32 GetMyNumber();

	UFUNCTION(BlueprintCallable)
	void WhenFindItem(int32 PlayerID);

	UPROPERTY(Meta = (BindWidget))
	class UImage* QuestionMark;

	UPROPERTY(Meta = ( BindWidget ))
	class UImage* Evidence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<class UTexture2D*> ItemColor;

	UPROPERTY()
	class UInventoryWidget* Inven;

	UPROPERTY()
	class UDescriptionWidget* DescriptionUI;

	UPROPERTY(meta = (BindWidget))
	class UButton* ItemButton;

	UFUNCTION()
	void ItemButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UImage* Player1Light;

	UPROPERTY(meta = (BindWidget))
	class UImage* Player2Light;

	UPROPERTY(meta = (BindWidget))
	class UImage* Player3Light;

	UPROPERTY()
	class ATP_ThirdPersonCharacter* me;

};
