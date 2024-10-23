// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_DevelopMapGameMode.h"

void AAJH_DevelopMapGameMode::ServerTravelToLevel_Implementation(const FString& LevelName)
{
    if ( HasAuthority() ) // 서버인지 확인
    {
        // 서버에서 레벨 이동을 처리
        GetWorld()->ServerTravel(LevelName);
    }
}

bool AAJH_DevelopMapGameMode::ServerTravelToLevel_Validate(const FString& LevelName)
{
	return true;
}
