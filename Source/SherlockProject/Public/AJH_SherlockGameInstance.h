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

	IOnlineSessionPtr sessionInterface;
	//���ǿ� ���õ� ��� ��Ʈ���� �ϴ� �⺻Ŭ����

	void CreateMySession();		// ��û�� ����� �ޱ� ���� �Լ�
	void FindMySession();
	void JoinMySession(int32 roomNumber);
	void ExitMySession();
	void SetSessionName(FString name, FString ClickedroomName_, FString ClickedhostName_, int32 ClickedplayerCount_);
	FORCEINLINE FString GetSessionName() { return mySessionName.ToString(); }

	void CreateOrFindMySession();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	FString ClickedroomName = FString("Crime_Scene");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	FString ClickedhostName= FString("Crime_Host");;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	int32 ClickedplayerCount=10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	FString UserNickName="None";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	int32 meshNum;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	TArray<FName> AllSessionNames;
	void OnDestroyAllSessions();
private:
	FName mySessionName = FName("first Session");
	TSharedPtr<class FOnlineSessionSearch> sessionSearch;	//OnlineSessionSearch �� 
	
	void OnCreatedSession(FName sessionName, bool bWasSuccessful);	//������ ���ǻ����� ��û�ϱ� ���� �Լ�
	void OnFoundSession(bool bwasSuccessful);
	void OnJoinedSession(FName SesssionName, EOnJoinSessionCompleteResult::Type result);
	void OnDestroyedSesssion(FName sessionName, bool bwasSuccessful);

};
