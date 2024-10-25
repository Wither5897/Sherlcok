// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_CrimeSceneTravelWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "AJH_SherlockGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerController.h"
#include "Jin/AJH_DevelopMapGameMode.h"

void UAJH_CrimeSceneTravelWidget::NativeConstruct()
{
	gi = GetGameInstance<UAJH_SherlockGameInstance>();
	Switcherindex->SetActiveWidgetIndex(0);

	Btn_Crimefirst->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Crimefirst);
	Btn_CrimeSecond->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Crimefirst);
	Btn_CrimeThird->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Crimefirst);
	Btn_Back->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Back);
	Btn_Back_0->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Back);
	Btn_Back_1->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Back);
	Btn_Back_2->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Back);
	Btn_FirstCrimeTravel->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_FirstCrimeTravel);
	//Btn_LevelBack->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_LevelBack);
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_Crimefirst()
{
	currentPageIndex = Switcherindex->GetActiveWidgetIndex();
	PageHistory.Add(currentPageIndex);

	Switcherindex->SetActiveWidgetIndex(1);
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_Back()
{
	if ( PageHistory.Num() > 0 )
	{
		lastPageIndex = PageHistory.Pop();
		Switcherindex->SetActiveWidgetIndex(lastPageIndex);
	}
	else if ( Btn_Back->IsPressed() )
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Switcherindex->SetActiveWidgetIndex(0);
	}

	/*if( Btn_Back )
	SetVisibility(ESlateVisibility::Hidden);

	if( Btn_Back_0 )
	Switcherindex->SetActiveWidgetIndex(0);

	if( Btn_Back_1 )
	Switcherindex->SetActiveWidgetIndex(0);

	if( Btn_Back_2 )
	Switcherindex->SetActiveWidgetIndex(0);*/

}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_FirstCrimeTravel()
{
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	//AAJH_DevelopMapGameMode* gm = Cast<AAJH_DevelopMapGameMode>(GetWorld()->GetAuthGameMode());
	if ( gi != nullptr&& pc->IsLocalPlayerController())
	{
		// GetWorld()->ServerTravel("/Game/Jin/Maps/SampleLevel", true);
		pc->ClientTravel(FString("/Game/Jin/Maps/MainDevelopCase"), ETravelType::TRAVEL_Absolute);
		// gm->ServerTravelToLevel("/Game/Jin/Maps/SampleLevel");
	}
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_LevelBack()
{
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	//AAJH_DevelopMapGameMode* gm = Cast<AAJH_DevelopMapGameMode>(GetWorld()->GetAuthGameMode());
	if ( gi != nullptr && pc->IsLocalPlayerController() )
	{
		// GetWorld()->ServerTravel("/Game/Jin/Maps/MyDevelopMap", true);
		// pc->ClientTravel(FString("/Game/Jin/Maps/MyDevelopMap"), ETravelType::TRAVEL_Absolute);
		//gm->ServerTravelToLevel("/Game/Jin/Maps/MyDevelopMap");
		//gi->FindMySession();
		pc->ClientTravel(FString("192.168.0.40:7777/Game/Jin/Maps/MainMyDevelopMap"), ETravelType::TRAVEL_Absolute);
	}
}
