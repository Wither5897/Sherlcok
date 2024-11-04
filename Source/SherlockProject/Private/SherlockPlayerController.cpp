// Fill out your copyright notice in the Description page of Project Settings.


#include "SherlockPlayerController.h"
#include "SherlockHUD.h"
#include "UW_Main.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Jin/AJH_UserNameWidgetComponent.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Jin/AJH_DevelopMapGameMode.h"
#include "AJH_SherlockGameInstance.h"
#include "SL_GameModeBase.h"
#include "../TP_ThirdPerson/TP_ThirdPersonGameMode.h"
#include "Components/TextBlock.h"

void ASherlockPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("Chat"), EInputEvent::IE_Pressed, this, &ASherlockPlayerController::FocusChatInputText);
}

void ASherlockPlayerController::SendMessage(const FText& Text)
{
	FString PlayerName;
	if ( auto* gi = Cast<UAJH_SherlockGameInstance>(GetWorld()->GetGameInstance()) )
	{
		PlayerName = gi->UserNickName;
	}
	FString Message = FString::Printf(TEXT("%s : %s"), *PlayerName, *Text.ToString());

	CtoS_SendMessage(Message);
}

void ASherlockPlayerController::FocusGame()
{
	SetInputMode(FInputModeGameOnly());
}

void ASherlockPlayerController::FocusChatInputText()
{
	ASherlockHUD* HUD = GetHUD<ASherlockHUD>();
	if ( HUD == nullptr ) return;

	if ( HUD->bIsChatOpen )
	{
		SetInputMode(FInputModeGameOnly());
		HUD->bIsChatOpen = false;
	}
	else
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(HUD->GetChatInputTextObject());
		SetInputMode(InputMode);
		HUD->bIsChatOpen = true;
	}
}

void ASherlockPlayerController::CtoS_SendMessage_Implementation(const FString& Message)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);
	for ( AActor* OutActor : OutActors )
	{
		ASherlockPlayerController* pc = Cast<ASherlockPlayerController>(OutActor);
		if ( pc )
		{
			bool bIsSender = (pc == this);
			pc->StoC_SendMessage(Message, bIsSender);
		}
	}
}

void ASherlockPlayerController::StoC_SendMessage_Implementation(const FString& Message, bool bIsSender)
{
	ASherlockHUD* HUD = GetHUD<ASherlockHUD>();
	if ( HUD == nullptr ) return;

	HUD->AddChatMessage(Message, bIsSender);

	// 클라는 아직 안됨. 멀티 수정 필요 
	if ( !HUD->bIsChatOpen && HUD->MainUIObject && HUD->MainUIObject->ChatNotificationText )
	{
		HUD->MainUIObject->ChatNotificationText->SetVisibility(ESlateVisibility::Visible);
	}
	else if ( HUD->bIsChatOpen && HUD->MainUIObject && HUD->MainUIObject->ChatNotificationText )
	{
		HUD->MainUIObject->ChatNotificationText->SetVisibility(ESlateVisibility::Hidden);
	}
}

//========================================================================================================

bool ASherlockPlayerController::ServerSetUserName_Validate(const FString& UserName)
{
	return true;
}

void ASherlockPlayerController::ServerSetUserName_Implementation(const FString& UserName)
{
	if ( HasAuthority() )
	{
		UE_LOG(LogTemp, Warning, TEXT("ServerSetUserName called on the server with UserName: %s"), *UserName);
		me = Cast<ATP_ThirdPersonCharacter>(GetPawn());
		if ( me )
		{
			UAJH_UserNameWidgetComponent* UserNameWidgetComp = me->FindComponentByClass<UAJH_UserNameWidgetComponent>();
			if ( UserNameWidgetComp )
			{
				UserNameWidgetComp->UserName = UserName;
				UserNameWidgetComp->SetUserName(UserName);
				UserNameWidgetComp->MultiCastSetUserName(UserName);
				UE_LOG(LogTemp, Warning, TEXT("Server set UserName: %s"), *UserNameWidgetComp->UserName);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("UserNameWidgetComp is NULL on the server"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ServerSetUserName failed: no authority on the server."));
	}
}

void ASherlockPlayerController::ServerReadyCount_Implementation(int32 ReadyCount)
{
	ATP_ThirdPersonGameMode* gm = Cast<ATP_ThirdPersonGameMode>(GetWorld()->GetAuthGameMode());
	gm->OnMyReadyCount(ReadyCount);
}

