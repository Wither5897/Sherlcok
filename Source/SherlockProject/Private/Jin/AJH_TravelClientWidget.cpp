// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_TravelClientWidget.h"
#include "Components/Button.h"
#include "../TP_ThirdPerson/TP_ThirdPersonGameMode.h"
#include "SherlockPlayerController.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"

void UAJH_TravelClientWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	pc = Cast<ASherlockPlayerController>(GetWorld()->GetFirstPlayerController());

	Btn_FirstCrimeReady->OnClicked.AddDynamic(this, &UAJH_TravelClientWidget::OnMyBtn_FirstCrimeReady);
	Btn_Cancel->OnClicked.AddDynamic(this, &UAJH_TravelClientWidget::OnMyBtn_Cancel);
	Btn_Crimefirst->OnClicked.AddDynamic(this, &UAJH_TravelClientWidget::OnMyBtn_Crimefirst);
	Btn_Back->OnClicked.AddDynamic(this, &UAJH_TravelClientWidget::OnMyBtn_Back);

	Btn_Cancel->SetVisibility(ESlateVisibility::Collapsed);
}

void UAJH_TravelClientWidget::OnMyBtn_Back()
{
	SetVisibility(ESlateVisibility::Collapsed);
	
}

void UAJH_TravelClientWidget::OnMyBtn_FirstCrimeReady()
{
	UGameplayStatics::PlaySound2D(GetWorld(), PaperscrollSound);
	SherlockPC = Cast<ASherlockPlayerController>(GetWorld()->GetFirstPlayerController());
	SherlockPC->ServerReadyCount(1);
	Btn_FirstCrimeReady->SetVisibility(ESlateVisibility::Collapsed);
	Btn_Cancel->SetVisibility(ESlateVisibility::Visible);
}

void UAJH_TravelClientWidget::OnMyBtn_Cancel()
{
	UGameplayStatics::PlaySound2D(GetWorld(), PaperscrollSound);
	SherlockPC = Cast<ASherlockPlayerController>(GetWorld()->GetFirstPlayerController());
	SherlockPC->ServerReadyCount(-1);
	Btn_Cancel->SetVisibility(ESlateVisibility::Collapsed);
	Btn_FirstCrimeReady->SetVisibility(ESlateVisibility::Visible);
}

void UAJH_TravelClientWidget::OnMyBtn_Crimefirst()
{
	UGameplayStatics::PlaySound2D(GetWorld(), PaperscrollSound);
	Switcherindex->SetActiveWidgetIndex(1);
}
