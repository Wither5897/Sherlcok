// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "AJH_SherlockGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UAJH_SherlockGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	// �¶��� ���� �������̽��� ����ϰ� �ʹ�.
	IOnlineSessionPtr sessionInterface;

	FString MySessionName = TEXT("CRIME_SCENE");

	// ����� ��û
	void CreateMySession(FString roomName, int32 playerCount); // ��û�� ����� �ޱ� ���� �Լ�
	// ����� ����
	void OnCreatedSession(FName sessionName, bool bWasSuccessful);

	// ã�� ���� ���
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	// �� ã�� ��û
	void FindOtherSessions();
	// �� ã�� ����
	void OnMyFindSessionsCompleteDelegates(bool bWasSuccessful);

	// �������� �ѱ��̸� ���� ���� ��ȸ�ϸ� �ѱ��� ������ �̽��߻�!!
	// Base64 ���ڵ����� �ذ��ϰ�����!
	FString StringBase64Encode(const FString& str);

	FString StringBase64Decode(const FString& str);

};
