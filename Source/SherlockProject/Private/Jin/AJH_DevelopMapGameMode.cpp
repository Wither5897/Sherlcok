// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_DevelopMapGameMode.h"

void AAJH_DevelopMapGameMode::ServerTravelToLevel_Implementation(const FString& LevelName)
{
    if ( HasAuthority() && UserReady >= 3 ) // 서버인지 확인
    {
        // 서버에서 레벨 이동을 처리
        GetWorld()->ServerTravel(LevelName, true);
    }
}

bool AAJH_DevelopMapGameMode::ServerTravelToLevel_Validate(const FString& LevelName)
{
	return true;
}

void AAJH_DevelopMapGameMode::OnMyReadyCount(int32 ReadyCount)
{
    UserReady += ReadyCount;
    UE_LOG(LogTemp, Warning, TEXT("Num : %d"), UserReady);
}
