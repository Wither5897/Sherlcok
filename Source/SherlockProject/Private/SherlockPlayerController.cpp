// Fill out your copyright notice in the Description page of Project Settings.


#include "SherlockPlayerController.h"
#include "SherlockHUD.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Jin/AJH_UserNameWidgetComponent.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Jin/AJH_DevelopMapGameMode.h"
#include "AJH_SherlockGameInstance.h"

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
	// PlayerName stema ID 
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

	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(HUD->GetChatInputTextObject());

	SetInputMode(InputMode);
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
			pc->StoC_SendMessage(Message);
		}
	}
}

void ASherlockPlayerController::StoC_SendMessage_Implementation(const FString& Message)
{
	ASherlockHUD* HUD = GetHUD<ASherlockHUD>();
	if ( HUD == nullptr ) return;

	HUD->AddChatMessage(Message);
}

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
	AAJH_DevelopMapGameMode* gm = Cast<AAJH_DevelopMapGameMode>(GetWorld()->GetAuthGameMode());
	gm->OnMyReadyCount(ReadyCount);
}

