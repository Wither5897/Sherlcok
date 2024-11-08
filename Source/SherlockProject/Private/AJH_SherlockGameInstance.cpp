// Fill out your copyright notice in the Description page of Project Settings.


#include "AJH_SherlockGameInstance.h"

#include "EditorDirectories.h"
#include "EngineUtils.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "SherlockProject.h"
#include "Online/OnlineSessionNames.h"
#include "string"
#include "../../../../Plugins/Online/OnlineBase/Source/Public/Online/OnlineSessionNames.h"
#include "Jin/AJH_UserNameTagWidget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Jin/AJH_UserNameWidgetComponent.h"
#include "Jin/AJH_WorldActor.h"
#include "Kismet/GameplayStatics.h"
#include "SK/MapSaveGame.h"

void UAJH_SherlockGameInstance::Init()
{
	Super::Init();

	sessionInterface = IOnlineSubsystem::Get()->GetSessionInterface();

	if (sessionInterface != nullptr)
	{
		//서버쪽에서 Delegate 으로 이벤트 값을 받을 함수를 연결
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
	SessionSettings->bIsDedicated = false; // 데디케이트 서버 사용안함
	SessionSettings->bAllowInvites = true; //초대기능 사용
	SessionSettings->bAllowJoinInProgress = true; // 진행중에도 들어오는것을 사용
	SessionSettings->bAllowJoinViaPresence = true;
	SessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
	// 접속하는 방법이 랜 경유 , 스팀서버 경유 두가지 있는데 랜 경유이면 null 문자열 반환, 스팀이면 steam 문자열 반환
	SessionSettings->bUsesPresence = true;
	SessionSettings->bShouldAdvertise = true; //다른사람이 세션검색할경우 노출되도록 ( 검색이 가능하도록 )
	SessionSettings->bUseLobbiesIfAvailable = true;  //로비의 사용여부
	SessionSettings->NumPublicConnections = 3;

	FName SessionName = FName(*FString::Printf(TEXT("MySession_%d"), FDateTime::Now().GetTicks()));

	//커스텀 설정값을 추가하기
	SessionSettings->Set(FName("Room Name"), ClickedroomName, EOnlineDataAdvertisementType::Type::ViaOnlineServiceAndPing);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

	sessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), SessionName, *SessionSettings);
	AllSessionNames.Add(SessionName);
	//서버에  이런 세팅값으로 만들어달라는 요청 ( 호출시점 에 session 이 완성된게 아님 )
	UE_LOG(LogTemp, Warning, TEXT("Try to create Session"));
	UE_LOG(LogTemp, Warning, TEXT("current platform : %s"), *IOnlineSubsystem::Get()->GetSubsystemName().ToString());
}

void UAJH_SherlockGameInstance::OnCreatedSession(FName sessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Session Name: %s"), *sessionName.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Session create: %s"), bWasSuccessful ? *FString("Success!") : *FString("Fail"));

	//멀티플레이를 할 맵으로 이동한다. 맵의 경로 작성해주기
	//GetWorld()->ServerTravel("/Game/Jin/Maps/MyDevelopMap?Listen", true);
	GetWorld()->ServerTravel("/Game/TJ/Main?Listen", true);
	//지금현재 리슨서버이기때문에  ?listen 으로 설정 
}

void UAJH_SherlockGameInstance::FindMySession()
{
	if (!sessionInterface.IsValid())
	{
		return;
	}

	// 세션 검색 조건을 설정하기
	sessionSearch = MakeShareable(new FOnlineSessionSearch());
	check(sessionSearch);
	sessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
	sessionSearch->MaxSearchResults = 3;
	sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Type::Equals);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	// 서버에 세션 검색을 요청하기
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

		// 어차피 방은 1개
		// 있으면 참여 , 없으면 만들기
		for (auto Result : results)
		{
			FString roomName;
			Result.Session.SessionSettings.Get(FName("Room Name"), roomName);

			if (roomName == FString("CUBIC")) // Crime_Scene
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
			pc->ClientTravel(FString("/Game/Jin/Maps/LobbyMap"), ETravelType::TRAVEL_Absolute);
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

void UAJH_SherlockGameInstance::SaveLevel(FString LevelName){
	UE_LOG(LogTemp, Warning, TEXT("Save Level"));
	UMapSaveGame* SaveGameInstance = Cast<UMapSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MyLevelSave"), 0));

	if(!SaveGameInstance){
		SaveGameInstance = Cast<UMapSaveGame>(UGameplayStatics::CreateSaveGameObject(UMapSaveGame::StaticClass()));
		if(!SaveGameInstance){
			return;
		}
	}
	
	FLevelSaveData* ExistingLevelData = SaveGameInstance->DataList.FindByPredicate([&](const FLevelSaveData& Data) {
		return Data.LevelName == LevelName;
	});

	if(!ExistingLevelData){
		FLevelSaveData NewLevelData;
		NewLevelData.LevelName = LevelName;
		SaveGameInstance->DataList.Add(NewLevelData);
		ExistingLevelData = &SaveGameInstance->DataList.Last();
	}
	else{
		ExistingLevelData->SavedActors.Empty();
	}
	
	for (TActorIterator<AAJH_WorldActor> ActorItr(GetWorld()); ActorItr; ++ActorItr){
		AAJH_WorldActor* Actor = *ActorItr;

		FActorSaveData ActorData;
		ActorData.Location = Actor->GetActorLocation();
		ActorData.Rotation = Actor->GetActorRotation();
		ActorData.Scale = Actor->GetActorScale3D();
		ActorData.ActorClass = Actor->GetClass();

		ExistingLevelData->SavedActors.Add(ActorData);
	}
	
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MyLevelSave"), 0);
}

void UAJH_SherlockGameInstance::LoadLevel(FString LevelName){
	UE_LOG(LogTemp, Warning, TEXT("Load Level"));
	LoadGameInstance = Cast<UMapSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MyLevelSave"), 0));

	if (!LoadGameInstance){
		return;
	}

	const FLevelSaveData* LevelData = LoadGameInstance->DataList.FindByPredicate([&](const FLevelSaveData& Data){
		return Data.LevelName == LevelName;
	});

	if(LevelData){
		for (const FActorSaveData& ActorData : LevelData->SavedActors){
			FActorSpawnParameters SpawnParams;
			AAJH_WorldActor* NewActor = GetWorld()->SpawnActor<AAJH_WorldActor>(ActorData.ActorClass, ActorData.Location, ActorData.Rotation, SpawnParams);
			if (!NewActor){
				return;
			}
			NewActor->SetActorScale3D(ActorData.Scale);
		}
	}
}

void UAJH_SherlockGameInstance::CreateOrFindMySession()
{
	// 버튼클릭해서
	// 검색한다음 없음 만들고 , 있으면 있는방으로 들어가기
	FindMySession();
}

void UAJH_SherlockGameInstance::UserNickNameToCharacter(ACharacter* player)
{
	if ( player )
	{
		UAJH_UserNameWidgetComponent* NameWidgetComp = player->FindComponentByClass<UAJH_UserNameWidgetComponent>();
		if ( NameWidgetComp )
		{
			NameWidgetComp->SetUserName(UserNickName);
			UE_LOG(LogTemp, Warning, TEXT("UserNickName set in GameInstance: %s"), *NameWidgetComp->UserName);
		}
	}
}