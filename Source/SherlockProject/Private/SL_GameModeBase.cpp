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
