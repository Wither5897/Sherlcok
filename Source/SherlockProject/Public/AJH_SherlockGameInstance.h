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

	// 온라인 세션 인터페이스를 기억하고 싶다.
	IOnlineSessionPtr sessionInterface;

	FString MySessionName = TEXT("CRIME_SCENE");

	// 방생성 요청
	void CreateMySession(FString roomName, int32 playerCount); // 요청한 결과를 받기 위한 함수
	// 방생성 응답
	void OnCreatedSession(FName sessionName, bool bWasSuccessful);

	// 찾을 방의 목록
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	// 방 찾기 요청
	void FindOtherSessions();
	// 방 찾기 응답
	void OnMyFindSessionsCompleteDelegates(bool bWasSuccessful);

	// 스팀으로 한글이름 방을 만들어서 조회하면 한글이 깨지는 이슈발생!!
	// Base64 인코딩으로 해결하고자함!
	FString StringBase64Encode(const FString& str);

	FString StringBase64Decode(const FString& str);

};
