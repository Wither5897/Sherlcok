// Fill out your copyright notice in the Description page of Project Settings.


#include "AJH_SherlockGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "SherlockProject.h"
#include "Online/OnlineSessionNames.h"
#include "string"
#include "../../../../Plugins/Online/OnlineBase/Source/Public/Online/OnlineSessionNames.h"

void UAJH_SherlockGameInstance::Init()
{
	Super::Init();

	if (auto* subSystem = IOnlineSubsystem::Get())
	{
		sessionInterface = subSystem->GetSessionInterface();
		// 방생성 요청 -> 응답
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UAJH_SherlockGameInstance::OnCreatedSession);
		// 방찾기 요청 -> 콜백함수 등록
		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UAJH_SherlockGameInstance::OnMyFindSessionsCompleteDelegates);
	}

	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, [&]() {
		CreateMySession(MySessionName, 3);
	}, 3, false);
}

void UAJH_SherlockGameInstance::CreateMySession(FString roomName, int32 playerCount)
{
	FOnlineSessionSettings settings;

	settings.bIsDedicated = false; // 전용 서버 사용 안함
	// LAN 선으로 매치하는가?
	FName subsysName = IOnlineSubsystem::Get()->GetSubsystemName();
	settings.bIsLANMatch = subsysName == "NULL";
	settings.bShouldAdvertise = true; // 초대 기능 사용
	settings.bUsesPresence = true; // 유저의 상태 정보 (온라인/자리비움 등등) 사용 여부
	settings.bAllowJoinInProgress = true; // 중간 난입 허용
	settings.bAllowJoinViaPresence = true; // 중간 난입 허용
	settings.NumPublicConnections = playerCount; // 최대 인원수

	// 커스텀 정보
	settings.Set(FName("ROOM_NAME"), StringBase64Encode(roomName), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	settings.Set(FName("HOST_NAME"), StringBase64Encode(MySessionName), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	FUniqueNetIdPtr netID = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();

	sessionInterface->CreateSession(*netID, FName(MySessionName), settings);

	PRINTLOG(TEXT("Create Session Start roomNamd : %s / hostName : %s"), *roomName, *MySessionName);

}

void UAJH_SherlockGameInstance::OnCreatedSession(FName sessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		PRINTLOG(TEXT("OnCreatedSession is Success~~~~~"));

		// 서버가 여행을 떠나고싶다.
		//GetWorld()->ServerTravel(TEXT(" "));
	}
	else
	{
		PRINTLOG(TEXT("OnCreatedSession is Failed!!!"));
	}
}

void UAJH_SherlockGameInstance::FindOtherSessions()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch);

	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	SessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
	SessionSearch->MaxSearchResults = 40;

	sessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UAJH_SherlockGameInstance::OnMyFindSessionsCompleteDelegates(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		TArray<FOnlineSessionSearchResult> results = SessionSearch->SearchResults;

		for (auto ret : results)
		{
			if (ret.IsValid() == false)
			{
				continue;
			}

			FString roomName;
			FString hostName;
			int32 maxPlayerCount;
			int32 currentPlayerCount;
			int32 pingMS;
			// 방 이름
			ret.Session.SessionSettings.Get(FName("ROOM_NAME"), roomName);
			// 호스트 이름
			ret.Session.SessionSettings.Get(FName("HOST_NAME"), hostName);
			// 최대 플레이어 수
			maxPlayerCount = ret.Session.SessionSettings.NumPublicConnections;
			// 입장한 플레이어 수(최대 - 남은)
			currentPlayerCount = maxPlayerCount - ret.Session.NumOpenPublicConnections;
			// 핑 정보
			pingMS = ret.PingInMs;
		}
	}
}

FString UAJH_SherlockGameInstance::StringBase64Encode(const FString& str)
{
	// Set 할 때 : FString -> UTF8 (std::string) -> TArray<uint8> -> base64 로 Encode
	std::string utf8String = TCHAR_TO_UTF8(*str);
	TArray<uint8> arrayData = TArray<uint8>((uint8*)(utf8String.c_str()),
		utf8String.length());
	return FBase64::Encode(arrayData);
}

FString UAJH_SherlockGameInstance::StringBase64Decode(const FString& str)
{
	// Get 할 때 : base64 로 Decode -> TArray<uint8> -> TCHAR
	TArray<uint8> arrayData;
	FBase64::Decode(str, arrayData);
	std::string ut8String((char*)(arrayData.GetData()), arrayData.Num());
	return UTF8_TO_TCHAR(ut8String.c_str());
}
