// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_ThirdPersonGameMode.h"
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

void ATP_ThirdPersonGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	AMultiPlayerState* ps = Cast<AMultiPlayerState>(NewPlayer->GetPlayerState<APlayerState>());
	if (ps)
	{
		ps->SetPlayerId(NumPlayers);
		NumPlayers++;
		
		UE_LOG(LogTemp, Warning, TEXT("Assigned PlayerID: %d"), ps->GetPlayerId());
	}
}
