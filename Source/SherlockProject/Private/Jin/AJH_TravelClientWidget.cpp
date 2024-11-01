// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_TravelClientWidget.h"
#include "Components/Button.h"
#include "../TP_ThirdPerson/TP_ThirdPersonGameMode.h"
#include "SherlockPlayerController.h"

void UAJH_TravelClientWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Btn_FirstCrimeReady->OnClicked.AddDynamic(this, &UAJH_TravelClientWidget::OnMyBtn_FirstCrimeReady);
	Btn_Cancel->OnClicked.AddDynamic(this, &UAJH_TravelClientWidget::OnMyBtn_Cancel);
}

void UAJH_TravelClientWidget::OnMyBtn_FirstCrimeReady()
{
	SherlockPC = Cast<ASherlockPlayerController>(GetWorld()->GetFirstPlayerController());
	SherlockPC->ServerReadyCount(1);
	Btn_FirstCrimeReady->SetVisibility(ESlateVisibility::Collapsed);
	Btn_Cancel->SetVisibility(ESlateVisibility::Visible);
}

void UAJH_TravelClientWidget::OnMyBtn_Cancel()
{
	SherlockPC = Cast<ASherlockPlayerController>(GetWorld()->GetFirstPlayerController());
	SherlockPC->ServerReadyCount(-1);
	Btn_Cancel->SetVisibility(ESlateVisibility::Collapsed);
	Btn_FirstCrimeReady->SetVisibility(ESlateVisibility::Visible);
}
