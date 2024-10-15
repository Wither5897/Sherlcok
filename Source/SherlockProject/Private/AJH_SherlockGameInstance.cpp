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
		// ����� ��û -> ����
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UAJH_SherlockGameInstance::OnCreatedSession);
		// ��ã�� ��û -> �ݹ��Լ� ���
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

	settings.bIsDedicated = false; // ���� ���� ��� ����
	// LAN ������ ��ġ�ϴ°�?
	FName subsysName = IOnlineSubsystem::Get()->GetSubsystemName();
	settings.bIsLANMatch = subsysName == "NULL";
	settings.bShouldAdvertise = true; // �ʴ� ��� ���
	settings.bUsesPresence = true; // ������ ���� ���� (�¶���/�ڸ���� ���) ��� ����
	settings.bAllowJoinInProgress = true; // �߰� ���� ���
	settings.bAllowJoinViaPresence = true; // �߰� ���� ���
	settings.NumPublicConnections = playerCount; // �ִ� �ο���

	// Ŀ���� ����
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

		// ������ ������ ������ʹ�.
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
			// �� �̸�
			ret.Session.SessionSettings.Get(FName("ROOM_NAME"), roomName);
			// ȣ��Ʈ �̸�
			ret.Session.SessionSettings.Get(FName("HOST_NAME"), hostName);
			// �ִ� �÷��̾� ��
			maxPlayerCount = ret.Session.SessionSettings.NumPublicConnections;
			// ������ �÷��̾� ��(�ִ� - ����)
			currentPlayerCount = maxPlayerCount - ret.Session.NumOpenPublicConnections;
			// �� ����
			pingMS = ret.PingInMs;
		}
	}
}

FString UAJH_SherlockGameInstance::StringBase64Encode(const FString& str)
{
	// Set �� �� : FString -> UTF8 (std::string) -> TArray<uint8> -> base64 �� Encode
	std::string utf8String = TCHAR_TO_UTF8(*str);
	TArray<uint8> arrayData = TArray<uint8>((uint8*)(utf8String.c_str()),
		utf8String.length());
	return FBase64::Encode(arrayData);
}

FString UAJH_SherlockGameInstance::StringBase64Decode(const FString& str)
{
	// Get �� �� : base64 �� Decode -> TArray<uint8> -> TCHAR
	TArray<uint8> arrayData;
	FBase64::Decode(str, arrayData);
	std::string ut8String((char*)(arrayData.GetData()), arrayData.Num());
	return UTF8_TO_TCHAR(ut8String.c_str());
}
