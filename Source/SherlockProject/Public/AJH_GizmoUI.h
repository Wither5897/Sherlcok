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

	UPROPERTY(EditDefaultsOnly, meta = ( bindWidget ))
	class UWidgetSwitcher* Switcher_GizmoUI;

	// ========================Location =============================================
	UPROPERTY(EditDefaultsOnly, meta=(bindWidget))
	class UEditableText* Edit_Location_X;
	UPROPERTY(EditDefaultsOnly, meta=(bindWidget))
	class UEditableText* Edit_Location_Y;
	UPROPERTY(EditDefaultsOnly, meta=(bindWidget))
	class UEditableText* Edit_Location_Z;

	UFUNCTION()
	void OnMyEdit_Location();
	UFUNCTION()
	void GetEdit_Location();
	UFUNCTION()
	void OnMyLocationTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	FString Location_X;
	FString Location_Y;
	FString Location_Z;

	FVector actorLocation;

	// ===================================== Rotation ============================================
	UPROPERTY(EditDefaultsOnly, meta=(bindWidget))
	class UEditableText* Edit_Rotation_Roll;
	UPROPERTY(EditDefaultsOnly, meta=(bindWidget))
	class UEditableText* Edit_Rotation_Pitch;
	UPROPERTY(EditDefaultsOnly, meta=(bindWidget))
	class UEditableText* Edit_Rotation_Yaw;
	UFUNCTION()
	void OnMyEdit_Rotation();
	UFUNCTION()
	void GetEdit_Rotation(FRotator NewRotation);
	UFUNCTION()
	void OnMyRotationTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	FString Rotation_Roll;
	FString Rotation_Pitch;
	FString Rotation_Yaw;

	FRotator actorRotation;

	// ====================================== Scale ================================
	UPROPERTY(EditDefaultsOnly, meta=(bindWidget))
	class UEditableText* Edit_Scale_X;
	UPROPERTY(EditDefaultsOnly, meta=(bindWidget))
	class UEditableText* Edit_Scale_Y;
	UPROPERTY(EditDefaultsOnly, meta=(bindWidget))
	class UEditableText* Edit_Scale_Z;
	UFUNCTION()
	void OnMyEdit_Scale();
	UFUNCTION()
	void GetEdit_Scale(FVector NewScale);
	UFUNCTION()
	void OnMyScaleTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	FString Scale_X;
	FString Scale_Y;
	FString Scale_Z;

	FVector actorScale;

	UPROPERTY()
	class AAJH_EditorCharacter* player;

};
