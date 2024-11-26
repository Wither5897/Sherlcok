// Fill out your copyright notice in the Description page of Project Settings.


#include "AJH_SherlockGameInstance.h"

// #include "EditorDirectories.h"
#include <ThirdParty/Steamworks/Steamv157/sdk/public/steam/isteamremotestorage.h>

#include "EngineUtils.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "SherlockProject.h"
#include "Online/OnlineSessionNames.h"
#include "string"
#include "TimerManager.h"
#include "../../../../Plugins/Online/OnlineBase/Source/Public/Online/OnlineSessionNames.h"
#include "Jin/AJH_UserNameTagWidget.h"
#include "Components/WidgetComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "Jin/AJH_UserNameWidgetComponent.h"
#include "Jin/AJH_WorldActor.h"
#include "Kismet/GameplayStatics.h"
#include "SherlockProject/TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "SK/EditIntroPlayWidget.h"
#include "SK/EditOutroPlayWidget.h"
#include "SK/EvidenceActorComp.h"
#include "SK/MapSaveGame.h"

#if WITH_EDITOR
#include "EditorDirectories.h"
#endif
#include "Jin/AJH_Sun.h"

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
	SessionSettings->bIsLANMatch = false;
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
	sessionSearch->bIsLanQuery = false;
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
			pc->ClientTravel(FString("/Game/Jin/Maps/MainLobbyMap"), ETravelType::TRAVEL_Absolute);
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

void UAJH_SherlockGameInstance::SaveLevel(FString LevelName, FText IntroTitle, FText IntroContext, FText OutroStory, float HeightSun){
	UE_LOG(LogTemp, Warning, TEXT("Save Level: %s"), *LevelName);
	UMapSaveGame* SaveGameInstance = Cast<UMapSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MyLevelSave"), 0));

	if (!SaveGameInstance){
		SaveGameInstance = Cast<UMapSaveGame>(UGameplayStatics::CreateSaveGameObject(UMapSaveGame::StaticClass()));
		if (!SaveGameInstance){
			UE_LOG(LogTemp, Error, TEXT("Failed to create SaveGame instance"));
			return;
		}
	}

	FLevelSaveData* ExistingLevelData = SaveGameInstance->DataList.FindByPredicate([&](const FLevelSaveData& Data) {
		return Data.LevelName == LevelName;
	});

	if (!ExistingLevelData){
		// 새 레벨 데이터 생성
		FLevelSaveData NewLevelData;
		NewLevelData.LevelName = LevelName;
		NewLevelData.IntroTitleText = IntroTitle;
		NewLevelData.IntroContextText = IntroContext;
		NewLevelData.OutroText = OutroStory;
		NewLevelData.HeightSun = HeightSun;
		SaveGameInstance->DataList.Add(NewLevelData);
		ExistingLevelData = &SaveGameInstance->DataList.Last();
		
		UE_LOG(LogTemp, Warning, TEXT("New Level Data Created"));
		UE_LOG(LogTemp, Warning, TEXT("New Level Data Created with HeightSun: %f"), HeightSun);
	}
	else{
		// 기존 레벨 데이터 업데이트
		ExistingLevelData->SavedActors.Empty();
		ExistingLevelData->IntroTitleText = IntroTitle;
		ExistingLevelData->IntroContextText = IntroContext;
		ExistingLevelData->OutroText = OutroStory;
		ExistingLevelData->HeightSun = HeightSun;
		
		UE_LOG(LogTemp, Warning, TEXT("Existing Level Data Updated"));
		UE_LOG(LogTemp, Warning, TEXT("Existing Level Data Updated with HeightSun: %f"), HeightSun);
	}

	// 저장된 텍스트 로그 출력
	UE_LOG(LogTemp, Warning, TEXT("Intro Title: %s"), *ExistingLevelData->IntroTitleText.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Intro Context: %s"), *ExistingLevelData->IntroContextText.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Outro Text: %s"), *ExistingLevelData->OutroText.ToString());
	UE_LOG(LogTemp, Warning, TEXT("HeightSun : %f"), ExistingLevelData->HeightSun);

	for (TActorIterator<AAJH_WorldActor> ActorItr(GetWorld()); ActorItr; ++ActorItr){
		AAJH_WorldActor* Actor = *ActorItr;

		FActorSaveData ActorData;
		ActorData.Location = Actor->GetActorLocation();
		ActorData.Rotation = Actor->GetActorRotation();
		ActorData.Scale = Actor->GetActorScale3D();
		ActorData.ActorClass = Actor->GetClass();
		ActorData.String = Actor->ExplainText;
		ActorData.boolean = Actor->bIsInterative;

		ExistingLevelData->SavedActors.Add(ActorData);
		UE_LOG(LogTemp, Warning, TEXT("String Text: %s"), *ActorData.String);
	}
    
	if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MyLevelSave"), 0)){
		UE_LOG(LogTemp, Warning, TEXT("SaveGame Successful"));
	} else {
		UE_LOG(LogTemp, Error, TEXT("SaveGame Failed"));
	}
}

void UAJH_SherlockGameInstance::LoadLevel(FString LevelName) {
	UE_LOG(LogTemp, Warning, TEXT("Load Level"));
	LoadGameInstance = Cast<UMapSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MyLevelSave"), 0));

	if (!LoadGameInstance) {
		UE_LOG(LogTemp, Warning, TEXT("No Save Game Found"));
		return;
	}

	const FLevelSaveData* LevelData = LoadGameInstance->DataList.FindByPredicate([&](const FLevelSaveData& Data) {
		return Data.LevelName == LevelName;
	});
	
	if (LevelData) {
		// Save data in instance temporarily for later
		CachedLevelData = *LevelData;
		int32 ActorIndex = 0;
		FName InteractTag = FName(TEXT("InteractObj"));
		for (const FActorSaveData& ActorData : LevelData->SavedActors){
			FActorSpawnParameters SpawnParams;
			AAJH_WorldActor* NewActor = GetWorld()->SpawnActor<AAJH_WorldActor>(ActorData.ActorClass, ActorData.Location, ActorData.Rotation, SpawnParams);
			if (!NewActor){
				continue;
			}
			NewActor->SetActorScale3D(ActorData.Scale);
			NewActor->ExplainText = ActorData.String; // 여기서 데이터 복원
			UE_LOG(LogTemp, Warning, TEXT("Loading ExplainText: %s"), *ActorData.String);
			NewActor->AddComponentByClass(UEvidenceActorComp::StaticClass(), false, FTransform(), false);
			if(!ActorData.boolean){
				continue;
			}
			if(!NewActor->Tags.Contains(InteractTag)){
				NewActor->Tags.Add(InteractTag);
				if(ActorIndex < 10){
					NewActor->Tags.Add(FName(*FString::Printf(TEXT("0%d"), ActorIndex)));
				}
				else{
					NewActor->Tags.Add(FName(*FString::Printf(TEXT("%d"), ActorIndex)));
				}
				UE_LOG(LogTemp, Warning, TEXT("Add Interact Tag Success Tag Number : %s"), *NewActor->Tags.Last().ToString());
				ActorIndex++;
			}
		}
		
		// Schedule UI update after delay
		GetWorld()->GetTimerManager().SetTimerForNextTick([this]() {
			auto* PlayerController = GetWorld()->GetFirstPlayerController();
			if (!PlayerController) return;

			auto* Character = Cast<ATP_ThirdPersonCharacter>(PlayerController->GetPawn());
			if (!Character || !Character->EditIntroUI) return;

			Character->EditIntroUI->IntroFullText = CachedLevelData.IntroContextText.ToString();
			Character->EditIntroUI->IntroTitleText = CachedLevelData.IntroTitleText;
			Character->EditOutroUI->OutroContext = CachedLevelData.OutroText;
			UE_LOG(LogTemp, Warning, TEXT("IntroFullText updated with delay: %s"), *CachedLevelData.IntroContextText.ToString());
		});

		// Load Sun height data and apply to AAJH_Sun
		TActorIterator<AAJH_Sun> SunIterator(GetWorld());
		if ( SunIterator ) {
			AAJH_Sun* SunActor = *SunIterator;
			SunActor->height_Sun = LevelData->HeightSun; // 불러온 데이터 적용
			UE_LOG(LogTemp, Warning, TEXT("Sun Height Applied: %f"), LevelData->HeightSun);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("No Sun Actor found in the level."));
		}

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("LevelData not found for level: %s"), *LevelName);
	}
}

void UAJH_SherlockGameInstance::SaveSimulationSlot(){
	FString SlotName = TEXT("SimulationSlot");
	UE_LOG(LogTemp, Warning, TEXT("Saving Simulation Data to Slot: %s"), *SlotName);

	UMapSaveGame* SaveGameInstance = Cast<UMapSaveGame>(UGameplayStatics::CreateSaveGameObject(UMapSaveGame::StaticClass()));
	if (!SaveGameInstance) {
		UE_LOG(LogTemp, Error, TEXT("Failed to create SaveGame instance for simulation slot"));
		return;
	}

	// 액터 데이터를 저장
	for (TActorIterator<AAJH_WorldActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		AAJH_WorldActor* Actor = *ActorItr;

		FActorSaveData ActorData;
		ActorData.Location = Actor->GetActorLocation();
		ActorData.Rotation = Actor->GetActorRotation();
		ActorData.Scale = Actor->GetActorScale3D();
		ActorData.ActorClass = Actor->GetClass();
		ActorData.String = Actor->ExplainText;
		ActorData.boolean = Actor->bIsInterative;

		SaveGameInstance->SimulationActors.Add(ActorData);
		UE_LOG(LogTemp, Warning, TEXT("Saved Actor: %s"), *Actor->GetName());
	}

	// 슬롯에 저장
	if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0)) {
		UE_LOG(LogTemp, Warning, TEXT("Simulation data saved successfully"));
	} else {
		UE_LOG(LogTemp, Error, TEXT("Failed to save simulation data"));
	}
}

void UAJH_SherlockGameInstance::LoadSimulationSlot(){
	FString SlotName = TEXT("SimulationSlot");
	UE_LOG(LogTemp, Warning, TEXT("Loading Simulation Data from Slot: %s"), *SlotName);

	LoadGameInstance = Cast<UMapSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	if (!LoadGameInstance) {
		UE_LOG(LogTemp, Warning, TEXT("No simulation data found in slot: %s"), *SlotName);
		return;
	}

	// 저장된 액터 데이터로 복원
	for (const FActorSaveData& ActorData : LoadGameInstance->SimulationActors) {
		FActorSpawnParameters SpawnParams;
		AAJH_WorldActor* NewActor = GetWorld()->SpawnActor<AAJH_WorldActor>(ActorData.ActorClass, ActorData.Location, ActorData.Rotation, SpawnParams);
		if (!NewActor) continue;

		NewActor->SetActorScale3D(ActorData.Scale);
		NewActor->ExplainText = ActorData.String;
		NewActor->bIsInterative = ActorData.boolean;

		UE_LOG(LogTemp, Warning, TEXT("Loaded Actor: %s"), *NewActor->GetName());
	}

	UE_LOG(LogTemp, Warning, TEXT("Simulation data loaded successfully"));
}

void UAJH_SherlockGameInstance::OnCharacterReady(ATP_ThirdPersonCharacter* Character){
	if (!Character || !Character->EditIntroUI) return;
	
	if(!LoadGameInstance){
		return;
	}
	
	const FLevelSaveData* LevelData = LoadGameInstance->DataList.FindByPredicate([&](const FLevelSaveData& Data){
		return Data.LevelName == LoadLevelName;
	});

	if (LevelData) {
		Character->EditIntroUI->IntroFullText = LevelData->IntroContextText.ToString();
		Character->EditIntroUI->IntroTitleText = LevelData->IntroTitleText;
		Character->EditOutroUI->OutroContext = LevelData->OutroText;
		UE_LOG(LogTemp, Warning, TEXT("IntroFullText updated in OnCharacterReady: %s"), *LevelData->IntroContextText.ToString());
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