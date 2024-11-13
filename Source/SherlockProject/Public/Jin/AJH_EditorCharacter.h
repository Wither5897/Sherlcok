// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "AJH_EditorCharacter.generated.h"

enum  class EGizmoState
{
	Location,
	Rotation,
	Scale,
};

UCLASS()
class SHERLOCKPROJECT_API AAJH_EditorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAJH_EditorCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* cameraComp;

	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext* IMC_EditorTool;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_LookMouse;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_EditorMove;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_LeftClick;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_RightClick;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_LineTraceLeftClick;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_changeLocation;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_changeRotation;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_changeScale;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_Escape;

	FVector2D MouseValue;

	void OnMyIA_LookMouse(const FInputActionValue& value);
	void OnMyIA_EditorMove(const FInputActionValue& value);
	void OnMyIA_LeftClick();
	void OnMyIA_EndLeftClick();
	void OnMyIA_RightClick();
	void OnMyIA_EndRightClick();
	void OnMyIA_StartLineTraceLeftClick();
	void OnMyIA_EndLineTraceLeftClick();
	void OnMyIA_changeLocation();
	void OnMyIA_changeRotation();
	void OnMyIA_changeScale();
	void OnMyIA_Escape();

	UPROPERTY()
	class APlayerController* pc;

	int32 IA_changeNum;

	FVector direction;
	bool bIsActorSpawn = false;
	bool bIsEditorActor = false;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> EditorWidgetFactory;
	UPROPERTY()
	class UAJH_EditorToolWidget* EditorWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> EscapeWidgetFactory;
	UPROPERTY()
	class UAJH_EscapeWidget* EscapeWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> EditorActorFactory;
	UPROPERTY()
	class AAJH_EditorActor* EditorActor;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> WorldActorFactory;
	UPROPERTY()
	class AAJH_WorldActor* WorldActor;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> SaveLevelWidgetFactory;
	UPROPERTY()
	class UAJH_GizmoUI* GizmoUI;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> GizmoUIFactory;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> FactoryChange;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* HeavystompSound;

	UPROPERTY()
	class USaveLevelUI* SaveLevelWidget;
	AAJH_WorldActor* CurrentWorldActor = nullptr;
	AAJH_WorldActor* LastInteractedWorldActor = nullptr;
	ETraceTypeQuery query;
	FHitResult outHit;

	float MovementScaleFactor = 10.0f;
	UPROPERTY()
	float DistanceMultiplier = 100.0f;
	FVector2D initialMousePosition;
	bool bIsGizmoLocationActive = false;
	bool bIsGizmoRotationActive = false;
	bool bIsGizmoScaleActive = false;

	FVector initialWorldLocation;
	FVector actorInitialLocation;
	FVector worldLocation;
	FVector worldDirection;
	FVector deltaLocation;
	FVector newLocation;
	FRotator initialWorldRotation;
	FRotator actorInitialRotation;
	FRotator newRotation;
	FRotator worldRotation;
	FRotator deltaRotation;
	FVector initialWorldScale;
	FVector newScale;
	FVector actorInitialScale;
	FVector worldScale;

	void OnMyEditorActorSpawn(bool bIsSpawn);
	void OnMyLineTrace();
	void OnMyHandleGizmoRotation();
	void OnMyHandleGizmoScale();
	void LocationGizmoForSetCollision();
	void RotationGizmoForSetCollision();
	void ScaleGizmoForSetCollision();
	void OnMyLocationGizmoMovement();

	void OnMyGizmoInteraction();
	void SetGizmoState(EGizmoState GizmoState);
	// 상태 정보를 저장할 변수 추가
	EGizmoState CurrentGizmoState = EGizmoState::Location;

};
