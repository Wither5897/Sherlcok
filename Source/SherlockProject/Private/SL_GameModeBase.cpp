// Fill out your copyright notice in the Description page of Project Settings.


#include "SL_GameModeBase.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "SherlockPlayerController.h"
#include "SherlockHUD.h"

ASL_GameModeBase::ASL_GameModeBase()
{
	DefaultPawnClass = ATP_ThirdPersonCharacter::StaticClass();
	PlayerControllerClass = ASherlockPlayerController::StaticClass();
	HUDClass = ASherlockHUD::StaticClass();
}

void ASL_GameModeBase::ServerTravelToLevel_Implementation(const FString& LevelName)
{
    if ( HasAuthority() && UserReady >= 3 ) // 서버인지 확인
    {
        // 서버에서 레벨 이동을 처리
        GetWorld()->ServerTravel(LevelName, true);
    }
}

bool ASL_GameModeBase::ServerTravelToLevel_Validate(const FString& LevelName)
{
    return true;
}

void ASL_GameModeBase::OnMyReadyCount(int32 ReadyCount)
{
    UserReady += ReadyCount;
    UE_LOG(LogTemp, Warning, TEXT("Num : %d"), UserReady);
}
