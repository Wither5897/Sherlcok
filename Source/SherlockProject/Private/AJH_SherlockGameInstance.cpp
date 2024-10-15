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

	sessionInterface = IOnlineSubsystem::Get()->GetSessionInterface();

	if (sessionInterface != nullptr)
	{
		//�����ʿ��� Delegate ���� �̺�Ʈ ���� ���� �Լ��� ����
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UAJH_SherlockGameInstance::OnCreatedSession);

		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UAJH_SherlockGameInstance::OnFoundSession);

		sessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UAJH_SherlockGameInstance::OnJoinedSession);

		sessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UAJH_SherlockGameInstance::OnDestroyedSesssion);
	}

}

void UAJH_SherlockGameInstance::SetSessionName(FString name, FString ClickedroomName_, FString ClickedhostName_, int32 ClickedplayerCount_)
{
	mySessionName = FName(*name);
	ClickedroomName = ClickedroomName_;
	ClickedhostName = ClickedhostName_;
	ClickedplayerCount = ClickedplayerCount_;
}

void UAJH_SherlockGameInstance::CreateMySession()
{
	if (!sessionInterface.IsValid())
	{
		return;
	}

	TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
	SessionSettings->bIsDedicated = false; // ��������Ʈ ���� ������
	SessionSettings->bAllowInvites = true; //�ʴ��� ���
	SessionSettings->bAllowJoinInProgress = true; // �����߿��� �����°��� ���
	SessionSettings->bAllowJoinViaPresence = true;
	SessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
	// �����ϴ� ����� �� ���� , �������� ���� �ΰ��� �ִµ� �� �����̸� null ���ڿ� ��ȯ, �����̸� steam ���ڿ� ��ȯ
	SessionSettings->bUsesPresence = true;
	SessionSettings->bShouldAdvertise = true; //�ٸ������ ���ǰ˻��Ұ�� ����ǵ��� ( �˻��� �����ϵ��� )
	SessionSettings->bUseLobbiesIfAvailable = true;  //�κ��� ��뿩��
	SessionSettings->NumPublicConnections = 10;

	FName SessionName = FName(*FString::Printf(TEXT("MySession_%d"), FDateTime::Now().GetTicks()));

	//Ŀ���� �������� �߰��ϱ�
	SessionSettings->Set(FName("Room Name"), ClickedroomName, EOnlineDataAdvertisementType::Type::ViaOnlineServiceAndPing);

	//SessionSettings->Set(FName("Host Name"),ClickedhostName,EOnlineDataAdvertisementType::Type::ViaOnlineServiceAndPing);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

	sessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), SessionName, *SessionSettings);
	AllSessionNames.Add(SessionName);
	//������  �̷� ���ð����� �����޶�� ��û ( ȣ����� �� session�� �ϼ��Ȱ� �ƴ� )
	UE_LOG(LogTemp, Warning, TEXT("Try to create Session"));
	UE_LOG(LogTemp, Warning, TEXT("current platform : %s"), *IOnlineSubsystem::Get()->GetSubsystemName().ToString());
}

void UAJH_SherlockGameInstance::OnCreatedSession(FName sessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Session Name: %s"), *sessionName.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Session create: %s"), bWasSuccessful ? *FString("Success!") : *FString("Fail"));

	//��Ƽ�÷��̸� �� ������ �̵��Ѵ�. ���� ��� �ۼ����ֱ�
	///Script/Engine.World'/Game/Maps/BattleMap.BattleMap' ���� ��� ��� �� �־��ָ� ��
	///Script/Engine.World'/Game/Master/AlphaMap_.AlphaMap_'
	//GetWorld()->ServerTravel("/Game/Master/AlphaMap_?Listen", true);
	GetWorld()->ServerTravel("/Game/Jin/Maps/MyDevelopMap?Listen", true);
	//�������� ���������̱⶧����  ?listen ���� ���� 
}

void UAJH_SherlockGameInstance::FindMySession()
{
	if (!sessionInterface.IsValid())
	{
		return;
	}

	// ���� �˻� ������ �����ϱ�
	sessionSearch = MakeShareable(new FOnlineSessionSearch());
	check(sessionSearch);
	sessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
	sessionSearch->MaxSearchResults = 10;
	sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Type::Equals);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	// ������ ���� �˻��� ��û�ϱ�
	sessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), sessionSearch.ToSharedRef());
}

void UAJH_SherlockGameInstance::OnFoundSession(bool bwasSuccessful)
{
	if (!sessionInterface.IsValid()) return;

	if (!sessionSearch)
	{
		UE_LOG(LogTemp, Warning, TEXT("sessionSearch Null"));
	}
	else
	{
		TArray<FOnlineSessionSearchResult> results = sessionSearch->SearchResults;

		UE_LOG(LogTemp, Warning, TEXT("Session Count: %d"), results.Num());

		// ������ ���� 1��
		// ������ ���� , ������ �����
		for (auto Result : results)
		{
			FString roomName;
			Result.Session.SessionSettings.Get(FName("Room Name"), roomName);

			if (roomName == FString("YJRoom"))
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(
						-1,
						15.f,
						FColor::Cyan,
						FString::Printf(TEXT("Joining Match Type: %s"), *roomName)
					);
				}
				if (!sessionInterface.IsValid()) return;
				FName SessionName = FName(*FString::Printf(TEXT("MySession_%d"), FDateTime::Now().GetTicks()));
				const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
				sessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), SessionName, Result);
				return;
			}
		}

		CreateMySession();

	}

	UE_LOG(LogTemp, Warning, TEXT("Find Results: %s"), bwasSuccessful ? *FString("Success!") : *FString("Failed..."));
}

void UAJH_SherlockGameInstance::JoinMySession(int32 roomNumber)
{
	if (!sessionInterface.IsValid()) return;

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

	TArray<FOnlineSessionSearchResult> results = sessionSearch->SearchResults;

	const FOnlineSessionSearchResult* realSession = &results[roomNumber];

	sessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), mySessionName, *realSession);
}

void UAJH_SherlockGameInstance::OnJoinedSession(FName SesssionName, EOnJoinSessionCompleteResult::Type result)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Cyan,
		FString::Printf(TEXT("Joined Session: %s"), *SesssionName.ToString())
	);

	if (!sessionInterface.IsValid())
	{
		return;
	}

	switch (result)
	{
	case EOnJoinSessionCompleteResult::Success:
	{
		UE_LOG(LogTemp, Warning, TEXT("Join Success!"));

		APlayerController* pc = GetWorld()->GetFirstPlayerController();
		FString url;
		sessionInterface->GetResolvedConnectString(SesssionName, url, NAME_GamePort);
		UE_LOG(LogTemp, Warning, TEXT("url: %s"), *url);

		pc->ClientTravel(url, ETravelType::TRAVEL_Absolute);

		break;
	}
	case EOnJoinSessionCompleteResult::SessionIsFull:
		UE_LOG(LogTemp, Warning, TEXT("Session is full..."));
		break;
	case EOnJoinSessionCompleteResult::SessionDoesNotExist:
		UE_LOG(LogTemp, Warning, TEXT("Session Does Not Exist..."));
		break;
	case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress:
		UE_LOG(LogTemp, Warning, TEXT("Could Not Retrieve Address..."));
		break;
	case EOnJoinSessionCompleteResult::AlreadyInSession:
		UE_LOG(LogTemp, Warning, TEXT("You are already in this session..."));
		break;
	case EOnJoinSessionCompleteResult::UnknownError:
		UE_LOG(LogTemp, Warning, TEXT("Unknown Error occurred!"));
		break;
	default:
		break;
	}
}

void UAJH_SherlockGameInstance::ExitMySession()
{
	sessionInterface->DestroySession(mySessionName);
}

void UAJH_SherlockGameInstance::OnDestroyedSesssion(FName sessionName, bool bwasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Destory Session: %s"), bwasSuccessful ? *FString("Success!") : *FString("Failed..."));

	if (bwasSuccessful)
	{
		APlayerController* pc = GetWorld()->GetFirstPlayerController();

		if (pc != nullptr)
		{
			pc->ClientTravel(FString("/Game/Maps/LobbyLevel"), ETravelType::TRAVEL_Absolute);
			// 
		}
	}
}

void UAJH_SherlockGameInstance::OnDestroyAllSessions()
{
	for (const FName& SessionName : AllSessionNames)
	{
		sessionInterface->DestroySession(SessionName);
	}
}

void UAJH_SherlockGameInstance::CreateOrFindMySession()
{
	// ��ưŬ���ؼ�
	// �˻��Ѵ��� ���� ����� , ������ �ִ¹����� ����
	FindMySession();
}