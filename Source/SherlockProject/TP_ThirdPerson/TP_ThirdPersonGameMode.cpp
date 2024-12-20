﻿// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_ThirdPersonGameMode.h"

#include "AJH_SherlockGameInstance.h"
#include "TimerManager.h"
#include "TP_ThirdPersonCharacter.h"
#include "SK/EditIntroPlayWidget.h"
#include "SK/MultiPlayerState.h"
#include "UObject/ConstructorHelpers.h"

ATP_ThirdPersonGameMode::ATP_ThirdPersonGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	NumPlayers = 0;
	bIsSoundOn = false;
}

void ATP_ThirdPersonGameMode::BeginPlay(){
	Super::BeginPlay();

	if(HasAuthority()){
		auto* gi = Cast<UAJH_SherlockGameInstance>(GetGameInstance());
		if(gi && gi->bShouldLoadLevel){
			gi->LoadLevel(gi->LoadLevelName);
			gi->bShouldLoadLevel = false;
			gi->LoadLevelName = "";
		}
	}
	if(!bIsSoundOn){
		auto* me = Cast<ATP_ThirdPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		if(me){
			me->PlayMapSound();
			bIsSoundOn = true;
		}
	}
}

void ATP_ThirdPersonGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if(NumPlayers < 3){
		APlayerState* ps = NewPlayer->GetPlayerState<APlayerState>();
		if(ps){
			ps->SetPlayerId(NumPlayers);
			NumPlayers++;
		}
	}
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [NewPlayer]() {
		auto* Character = Cast<ATP_ThirdPersonCharacter>(NewPlayer->GetCharacter());
		if (Character && Character->EditIntroUI) {
			FString MapName = NewPlayer->GetWorld()->GetMapName();
			MapName.RemoveFromStart(NewPlayer->GetWorld()->StreamingLevelsPrefix);

			if (MapName == "SK_LoadMap" || MapName == "SK_LoadMap1") {
				Character->EditIntroUI->PlayStart();
				Character->EditIntroUI->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}, 0.3f, false);
}

void ATP_ThirdPersonGameMode::ServerTravelToLevel_Implementation(const FString& LevelName)
{
	if ( HasAuthority() && UserReady >= 3 || HasAuthority() && UserReady >= 1 ) // 서버인지 확인
	{
		// 서버에서 레벨 이동을 처리
		GetWorld()->ServerTravel(LevelName, true);
	}
}

void ATP_ThirdPersonGameMode::OnMyReadyCount(int32 ReadyCount)
{
	UserReady += ReadyCount;
	UE_LOG(LogTemp, Warning, TEXT("Num : %d"), UserReady);
}
