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
	class UInputMappingContext* IMC_EditorTool;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_LookMouse;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_EditorMove;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_LeftClick;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_RightClick;

	void OnMyIA_LookMouse(const FInputActionValue& value);
	void OnMyIA_EditorMove(const FInputActionValue& value);
	void OnMyIA_LeftClick();
	void OnMyIA_RightClick();

	UPROPERTY()
	class APlayerController* pc;

	FVector direction;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> EditorWidgetFactory;
	UPROPERTY()
	class UAJH_EditorToolWidget* EditorWidget;

};
