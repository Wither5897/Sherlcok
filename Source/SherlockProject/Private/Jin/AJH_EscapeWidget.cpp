// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_EscapeWidget.h"
#include "Components/Button.h"
#include "AJH_SherlockGameInstance.h"
#include "GameFramework/PlayerController.h"
#include "Jin/AJH_EditorCharacter.h"
#include "Kismet/GameplayStatics.h"

void UAJH_EscapeWidget::NativeConstruct()
{
	Escape_Btn_Yes->OnClicked.AddDynamic(this, &UAJH_EscapeWidget::OnMyEscape_Btn_Yes);
	Escape_Btn_No->OnClicked.AddDynamic(this, &UAJH_EscapeWidget::OnMyEscape_Btn_No);

	gi = GetGameInstance<UAJH_SherlockGameInstance>();
	pc = GetWorld()->GetFirstPlayerController();
	me = Cast<AAJH_EditorCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_EditorCharacter::StaticClass()));
}

void UAJH_EscapeWidget::OnMyEscape_Btn_Yes()
{
	if ( gi != nullptr )
	{
		// gi->FindMySession();
		pc->ClientTravel("/Game/TJ/Main?Listen", TRAVEL_Absolute);
		pc->SetInputMode(FInputModeGameOnly());
	}
}

void UAJH_EscapeWidget::OnMyEscape_Btn_No()
{
	SetVisibility(ESlateVisibility::Collapsed);
}
