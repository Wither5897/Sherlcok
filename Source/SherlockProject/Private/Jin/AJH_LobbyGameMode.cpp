// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_LobbyGameMode.h"
#include "AJH_LoginWidget.h"
#include "InterchangeResult.h"
#include "OnlineSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"
#include "GameFramework/PlayerState.h"
#include "Misc/CoreDelegates.h"
#include "SK/MultiPlayerState.h"
#include "ThirdParty/Steamworks/Steamv157/sdk/public/steam/steam_api.h"

#pragma comment(lib, "ThirdParty/Steamworks/Steamv157/sdk/redistributable_bin/win64/steam_api64.lib")

void AAJH_LobbyGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (LoginWidget != nullptr)
	{
		LoginUI = CreateWidget<UAJH_LoginWidget>(GetWorld(), LoginWidget);
		if (LoginUI != nullptr)
		{
			LoginUI->AddToViewport();
			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

			// 스팀서버 접속이라면

			if (IOnlineSubsystem::Get()->GetSubsystemName() == "STEAM")
			{
				if (SteamAPI_Init())
				{
					CSteamID steamID = SteamUser()->GetSteamID();
					const char* nickname = SteamFriends()->GetPersonaName();
					UE_LOG(LogTemp, Log, TEXT("Steam Nickname: %s"), UTF8_TO_TCHAR(nickname));
					LoginUI->Edit_hostName->SetText(FText::FromString(UTF8_TO_TCHAR(nickname)));
				}
			}
			else
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,"No Steam login");
				// LoginUI->Edit_hostName->SetHintText(FText::FromString(TEXT("닉네임 입력창")));
			}
		}
	}
}