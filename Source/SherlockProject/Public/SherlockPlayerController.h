// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SherlockPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API ASherlockPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;


	void SendMessage(const FText& Text);

	UFUNCTION()
	void FocusGame();

	UFUNCTION()
	void FocusChatInputText();

	UPROPERTY()
	class ATP_ThirdPersonCharacter* me;

	UFUNCTION(Server , Unreliable)
	void CtoS_SendMessage(const FString& Message);

	UFUNCTION(Client , Unreliable)
	void StoC_SendMessage(const FString& Message);


	// 서버로 닉네임을 전송하는 RPC 함수
	UFUNCTION(Server, Reliable)
	void ServerSetUserName(const FString& UserName);
	

};
