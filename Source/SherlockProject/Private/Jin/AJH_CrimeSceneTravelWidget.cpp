// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_CrimeSceneTravelWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "AJH_SherlockGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerController.h"
#include "SherlockPlayerController.h"
#include "../TP_ThirdPerson/TP_ThirdPersonGameMode.h"
#include "Components/TextBlock.h"
#include "Internationalization/Text.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void UAJH_CrimeSceneTravelWidget::NativeConstruct()
{
	// 사용할 애들 미리 선언해두기
	player = Cast<ATP_ThirdPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	SherlockPC = GetOwningPlayer<ASherlockPlayerController>();
	gi = GetGameInstance<UAJH_SherlockGameInstance>();
	gm = Cast<ATP_ThirdPersonGameMode>(GetWorld()->GetAuthGameMode());
	LoadGameInstance = Cast<UMapSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MyLevelSave"), 0));
	
	// 첫 번째 사건 버튼 바인딩
	Btn_Crimefirst->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Crimefirst);
	Btn_Crimefirst->OnHovered.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyAnim_Btn_CrimefirstHoVered);
	Btn_Crimefirst->OnUnhovered.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyAnim_Btn_CrimefirstUnHoVered);
	Btn_FirstCrimeTravel->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_FirstCrimeTravel);
	Btn_FirstCrimeReady->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Ready);

	// 두 번째 사건 버튼 바인딩
	Btn_CrimeSecond->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_CrimeSecond);
	Btn_SecondCrimeTravel->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_SecondCrimeTravel);
	Btn_SecondCrimeReady->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Ready);

	// 세 번째 사건 버튼 바인딩
	Btn_CrimeThird->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_CrimeThird);
	Btn_ThirdCrimeTravel->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_ThirdCrimeTravel);
	Btn_ThirdCrimeReady->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Ready);

	// 공통 버튼 바인딩
	Btn_Back->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Back);
	Btn_Back_0->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Back);
	Btn_Back_1->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Back);
	Btn_Back_2->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Back);
	Btn_Cancel->OnClicked.AddDynamic(this, &UAJH_CrimeSceneTravelWidget::OnMyBtn_Cancel);

	// Default Setting When Begin
	Switcherindex->SetActiveWidgetIndex(0);
	Btn_Cancel->SetVisibility(ESlateVisibility::Collapsed);
	RefreshList();
}

void UAJH_CrimeSceneTravelWidget::OnTextCrimeName()
{
	// CrimeName = FText::FromString(FString::Printf(TEXT("여고생 살인사건")));
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_Crimefirst()
{
	Switcherindex->SetActiveWidgetIndex(1);
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_CrimeSecond(){
	if (LoadGameInstance->DataList.Num() < 1){
		return;
	}
	Switcherindex->SetActiveWidgetIndex(2);
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_CrimeThird(){
	if (LoadGameInstance->DataList.Num() < 2){
		return;
	}
	Switcherindex->SetActiveWidgetIndex(3);
}

void UAJH_CrimeSceneTravelWidget::OnMyAnim_Btn_CrimefirstHoVered()
{
	PlayAnimationForward(Anim_Btn_Crimefirst);
}

void UAJH_CrimeSceneTravelWidget::OnMyAnim_Btn_CrimefirstUnHoVered()
{
	PlayAnimationReverse(Anim_Btn_Crimefirst);
}

void UAJH_CrimeSceneTravelWidget::OnMyAnim_Switcherindex()
{
	
}

void UAJH_CrimeSceneTravelWidget::OnMyAnim_Canvas_First()
{
	Switcherindex->SetActiveWidgetIndex(1);
}

void UAJH_CrimeSceneTravelWidget::OnMyAnim_Canvas_Second()
{
	Switcherindex->SetActiveWidgetIndex(2);
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_Back()
{
	Switcherindex->SetActiveWidgetIndex(0);
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_Ready()
{
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
	if ( gm != nullptr && SherlockPC->HasAuthority() )
	{
		gm->ServerTravelToLevel("/Game/TJ/Case?Listen");
		if ( player && player->IsLocallyControlled() )
		{
			SherlockPC->SetInputMode(FInputModeGameOnly());
		}
	}
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_SecondCrimeTravel(){
	if (LoadGameInstance->DataList.Num() < 1){
		return;
	}
	if ( gm != nullptr && SherlockPC->HasAuthority() )
	{
		gm->ServerTravelToLevel("/Game/SK/Map/SK_LoadMap?Listen");
		if ( player && player->IsLocallyControlled() )
		{
			SherlockPC->SetInputMode(FInputModeGameOnly());
			gi->bShouldLoadLevel = true;
			gi->LoadLevelName = LoadGameInstance->DataList[LoadGameInstance->DataList.Num() - 2].LevelName;
		}
	}
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_ThirdCrimeTravel(){
	if (LoadGameInstance->DataList.Num() < 2){
		return;
	}
	if ( gm != nullptr && SherlockPC->HasAuthority() )
	{
		gm->ServerTravelToLevel("/Game/SK/Map/SK_LoadMap1?Listen");
		if ( player && player->IsLocallyControlled() )
		{
			SherlockPC->SetInputMode(FInputModeGameOnly());
			gi->bShouldLoadLevel = true;
			gi->LoadLevelName = LoadGameInstance->DataList[LoadGameInstance->DataList.Num() - 1].LevelName;
		}
	}
}

void UAJH_CrimeSceneTravelWidget::OnMyBtn_LevelBack()
{
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if ( gi != nullptr && pc->IsLocalPlayerController() )
	{
		pc->ClientTravel(FString("192.168.0.40:7777/Game/TJ/Main?"), ETravelType::TRAVEL_Absolute);
	}
}

void UAJH_CrimeSceneTravelWidget::RefreshList(){
	if(!LoadGameInstance){
		return;
	}
	if(LoadGameInstance->DataList.Num() > 0){
		FText Temptext = FText::FromString(FString::Printf(TEXT("%s"), *LoadGameInstance->DataList[LoadGameInstance->DataList.Num() - 1].LevelName));
		Txt_CrimeName_1->SetText(Temptext);
	}
	if(LoadGameInstance->DataList.Num() > 1){
		FText Temptext = FText::FromString(FString::Printf(TEXT("%s"), *LoadGameInstance->DataList[LoadGameInstance->DataList.Num() - 2].LevelName));
		Txt_CrimeName_2->SetText(Temptext);
	}
}

