// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "AJH_EditorToolPawn.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API AAJH_EditorToolPawn : public ASpectatorPawn
{
	GENERATED_BODY()
	
public:
	AAJH_EditorToolPawn();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext* IMC_EditorTool;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_LeftClick;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_RightClick;

	void OnMyIA_LeftClick();
	void OnMyIA_RightClick();
	void OnMyMouseActionCanceled();


	UPROPERTY()
	class APlayerController* pc;


};
