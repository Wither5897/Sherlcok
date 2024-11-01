// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_CrimeSceneTravelWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "AJH_SherlockGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerController.h"
#include "Jin/AJH_DevelopMapGameMode.h"
#include "SherlockPlayerController.h"
#include "SL_GameModeBase.h"
#include "../TP_ThirdPerson/TP_ThirdPersonGameMode.h"
#include "Components/TextBlock.h"
#include "Internationalization/Text.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Animation/WidgetAnimationEvents.h"

void UAJH_CrimeSceneTravelWidget::NativeConstruct()
{
	gi = GetGameInstance<UAJH_SherlockGameInstance>();
	Switcherindex->SetActiveWidgetIndex(0);
	SherlockPC = GetOwningPlayer<ASherlockPlayerController>();

	Btn_Crimefirst->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Crimefirst);
	Btn_Crimefirst->OnHovered.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyAnim_Btn_CrimefirstHoVered);
	Btn_Crimefirst->OnUnhovered.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyAnim_Btn_CrimefirstUnHoVered);
	Btn_CrimeSecond->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Crimefirst);
	Btn_CrimeThird->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Crimefirst);
	Btn_Back->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Back);
	Btn_Back_0->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Back);
	Btn_Back_1->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Back);
	Btn_Back_2->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Back);
	Btn_FirstCrimeTravel->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_FirstCrimeTravel);
	Btn_FirstCrimeReady->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Ready);
	Btn_Cancel->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Cancel);
	Btn_SecondCrimeTravel->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_FirstCrimeTravel);
	Btn_SecondCrimeReady->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Ready);
	Btn_ThirdCrimeTravel->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_FirstCrimeTravel);
	Btn_ThirdCrimeReady->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Ready);
	//Btn_LevelBack->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_LevelBack);
	
	Btn_Cancel->SetVisibility(ESlateVisibility::Collapsed);

	if ( Anim_Canvas_First )
	{
		FWidgetAnimationDynamicEvent AnimationFinishedEvent;
		AnimationFinishedEvent.BindUFunction(this, FName("OnMyAnim_Canvas_First"));
		BindToAnimationFinished(Anim_Canvas_First, AnimationFinishedEvent);
		// BindToAnimationFinished(Anim_Switcherindex, this, &UAJH_CrimeSceneTravelWidget::OnMyAnim_Canvas_First);
	}

}

void UAJH_CrimeSceneTravelWidget::OnTextCrimeName()
{
	// CrimeName = FText::FromString(FString::Printf(TEXT("여고생 살인사건")));
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_Crimefirst()
{
	currentPageIndex = Switcherindex->GetActiveWidgetIndex();
	PageHistory.Add(currentPageIndex);
	UUserWidget::PlayAnimationForward(Anim_Canvas_First);

	//Switcherindex->SetActiveWidgetIndex(1);
}

void UAJH_CrimeSceneTravelWidget::OnMyAnim_Btn_CrimefirstHoVered()
{
	UUserWidget::PlayAnimationForward(Anim_Btn_Crimefirst);
}

void UAJH_CrimeSceneTravelWidget::OnMyAnim_Btn_CrimefirstUnHoVered()
{
	UUserWidget::PlayAnimationReverse(Anim_Btn_Crimefirst);
}

void UAJH_CrimeSceneTravelWidget::OnMyAnim_Switcherindex()
{
	UUserWidget::PlayAnimationForward(Anim_Switcherindex);
}

void UAJH_CrimeSceneTravelWidget::OnMyAnim_Canvas_First()
{
	Switcherindex->SetActiveWidgetIndex(1);
	UUserWidget::PlayAnimationForward(Anim_Canvas_Second);
	UUserWidget::PlayAnimationReverse(Anim_Canvas_First);
	//UUserWidget::PlayAnimationForward(Anim_Switcherindex);
}

void UAJH_CrimeSceneTravelWidget::OnMyAnim_Canvas_Second()
{
	// UUserWidget::PlayAnimationForward(Anim_Canvas_Second);
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
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_Ready()
{
	//AAJH_DevelopMapGameMode* gm = Cast<AAJH_DevelopMapGameMode>(GetWorld()->GetAuthGameMode());
	//gm->OnMyReadyCount(1);
	SherlockPC = Cast<ASherlockPlayerController>(GetWorld()->GetFirstPlayerController());
	SherlockPC->ServerReadyCount(1);

	Btn_FirstCrimeReady->SetVisibility(ESlateVisibility::Collapsed);
	Btn_Cancel->SetVisibility(ESlateVisibility::Visible);
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_Cancel()
{
	SherlockPC = Cast<ASherlockPlayerController>(GetWorld()->GetFirstPlayerController());
	SherlockPC->ServerReadyCount(-1);

	Btn_Cancel->SetVisibility(ESlateVisibility::Collapsed);
	Btn_FirstCrimeReady->SetVisibility(ESlateVisibility::Visible);
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_FirstCrimeTravel()
{
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	SherlockPC = Cast<ASherlockPlayerController>(GetWorld()->GetFirstPlayerController());
	player = Cast<ATP_ThirdPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	//AAJH_DevelopMapGameMode* gm = Cast<AAJH_DevelopMapGameMode>(GetWorld()->GetAuthGameMode());
	ATP_ThirdPersonGameMode* gm = Cast<ATP_ThirdPersonGameMode>(GetWorld()->GetAuthGameMode());
	if ( gi != nullptr&& pc->HasAuthority() )
	{
		// GetWorld()->ServerTravel("/Game/Jin/Maps/SampleLevel", true);
		// pc->ClientTravel(FString("/Game/Jin/Maps/MainDevelopCase"), ETravelType::TRAVEL_Absolute);
		gm->ServerTravelToLevel("/Game/TJ/Case?Listen");
		if ( player && player->IsLocallyControlled() )
		{
			SherlockPC->SetInputMode(FInputModeGameOnly());
		}
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
		pc->ClientTravel(FString("192.168.0.40:7777/Game/TJ/Main?"), ETravelType::TRAVEL_Absolute);
	}
}
