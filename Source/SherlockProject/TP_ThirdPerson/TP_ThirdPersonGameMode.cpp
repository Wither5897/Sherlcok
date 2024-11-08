// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_ThirdPersonGameMode.h"

#include "AJH_SherlockGameInstance.h"
#include "TimerManager.h"
#include "TP_ThirdPersonCharacter.h"
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
}

void ATP_ThirdPersonGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if(NewPlayer){
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDel;
		TimerDel.BindLambda([this, NewPlayer](){
			if (AMultiPlayerState* ps = NewPlayer->GetPlayerState<AMultiPlayerState>())
			{
				ps->SetPlayerId(NumPlayers);
				NumPlayers++;
                
				UE_LOG(LogTemp, Warning, TEXT("Assigned PlayerID: %d"), ps->GetPlayerId());
			}
		});
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 0.1f, false);
	}
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
