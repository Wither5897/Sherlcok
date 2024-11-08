// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "AJH_EditorCharacter.generated.h"

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

	void OnMyIA_LookMouse(const FInputActionValue& value);
	void OnMyIA_EditorMove(const FInputActionValue& value);
	void OnMyIA_LeftClick();
	void OnMyIA_RightClick();
	void OnMyIA_StartLineTraceLeftClick();
	void OnMyIA_EndLineTraceLeftClick();

	UPROPERTY()
	class APlayerController* pc;

	FVector direction;
	bool bIsActorSpawn = false;
	bool bIsEditorActor = false;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> EditorWidgetFactory;
	UPROPERTY()
	class UAJH_EditorToolWidget* EditorWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> EditorActorFactory;
	UPROPERTY()
	class AAJH_EditorActor* EditorActor;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> WorldActorFactory;
	UPROPERTY()
	class AAJH_WorldActor* WorldActor;
	AAJH_WorldActor* CurrentWorldActor = nullptr;
	AAJH_WorldActor* LastInteractedWorldActor = nullptr;
	ETraceTypeQuery query;
	FHitResult outHit;

	float MovementScaleFactor = 10.0f;
	UPROPERTY()
	float DistanceMultiplier = 100.0f;
	FVector2D initialMousePosition;

	FVector initialWorldLocation;
	FVector actorInitialLocation;
	FRotator actorInitialRotation;
	FVector worldLocation;
	FVector worldDirection;
	FVector deltaLocation;
	FVector newLocation;

	void OnMouseUpdateActorLocation();

	void OnMyEditorActorSpawn(bool bIsSpawn, int32 num);
	void OnMyLineTrace();

};
