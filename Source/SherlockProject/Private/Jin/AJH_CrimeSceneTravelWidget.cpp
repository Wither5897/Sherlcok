// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_CrimeSceneTravelWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "AJH_SherlockGameInstance.h"
#include "Net/UnrealNetwork.h"

void UAJH_CrimeSceneTravelWidget::NativeConstruct()
{
	gi = GetGameInstance<UAJH_SherlockGameInstance>();
	Switcherindex->SetActiveWidgetIndex(0);
	Btn_Crimefirst->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Crimefirst);
	Btn_Back->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Back);
	Btn_FirstCrimeTravel->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_FirstCrimeTravel);
	Btn_LevelBack->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_LevelBack);
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_Crimefirst()
{
	Switcherindex->SetActiveWidgetIndex(1);
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_Back()
{
	Switcherindex->SetActiveWidgetIndex(0);
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_FirstCrimeTravel()
{
	if ( gi != nullptr )
	{
		GetWorld()->ServerTravel("/Game/Jin/Maps/SampleLevel?Listen", true);
	}
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_LevelBack()
{
	if ( gi != nullptr )
	{
		GetWorld()->ServerTravel("/Game/Jin/Maps/MyDevelopMap?Listen", true);
	}
}
