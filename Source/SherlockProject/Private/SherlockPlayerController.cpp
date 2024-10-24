// Fill out your copyright notice in the Description page of Project Settings.


#include "SherlockPlayerController.h"
#include "SherlockHUD.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

void ASherlockPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("Chat"), EInputEvent::IE_Pressed, this, &ASherlockPlayerController::FocusChatInputText);
}

void ASherlockPlayerController::SendMessage(const FText& Text)
{
	FString PlayerName;
	FString Message = FString::Printf(TEXT("%s : %s"), *PlayerName, *Text.ToString());
	// PlayerName stema ID 
	CtoS_SendMessage(Message);
}

void ASherlockPlayerController::FocusGame()
{
	SetInputMode(FInputModeGameAndUI());
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
