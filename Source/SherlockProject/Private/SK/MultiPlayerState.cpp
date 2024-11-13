// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/MultiPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "SherlockProject/TP_ThirdPerson/TP_ThirdPersonCharacter.h"

AMultiPlayerState::AMultiPlayerState()
{
	// 레플리케이션 활성화
	bReplicates = true;
}

void AMultiPlayerState::SetPlayerIdNum(int32 newPlayerID){
	PlayerIDNum = newPlayerID;
	if(HasAuthority()){
		OnRep_PlayerIDNum();
	}
}

void AMultiPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMultiPlayerState, PlayerIDNum);
}

void AMultiPlayerState::OnRep_PlayerIDNum(){
	if(auto* me = Cast<ATP_ThirdPersonCharacter>(GetPawn())){
		me->ServerSetCharacterMaterial(GetPlayerIdNum());
	}
}
