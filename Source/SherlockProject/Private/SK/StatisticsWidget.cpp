// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/StatisticsWidget.h"

#include "SherlockPlayerController.h"
#include "Components/Button.h"
#include "Jin/AJH_SummaryWidget.h"
#include "SherlockProject/TP_ThirdPerson/TP_ThirdPersonCharacter.h"

void UStatisticsWidget::NativeOnInitialized(){
	Super::NativeOnInitialized();

	OnVisibilityChanged.AddDynamic(this, &UStatisticsWidget::OnVisibilityChange);
}

void UStatisticsWidget::NativeConstruct(){
	Super::NativeConstruct();

	me = Cast<ATP_ThirdPersonCharacter>(GetOwningPlayer()->GetCharacter());
	ExitButton->OnClicked.AddDynamic(this, &UStatisticsWidget::UStatisticsWidget::OnClickedExit);
}

void UStatisticsWidget::OnVisibilityChange(ESlateVisibility InVisibility){
	if (InVisibility == ESlateVisibility::Visible){
		UpdateStatistics();
	}
}

void UStatisticsWidget::UpdateStatistics(){
	CalcSuspectRank();
	CalcWeaponRank();
	CalcMainEviRank();
	CalcSpecialRank();
}

void UStatisticsWidget::CalcSuspectRank(){
	me->SummaryWidget->LoadClueData();
	TArray<TPair<int32, int32>> SuspectPairs;
	for (int32 i = 0; i < me->SummaryWidget->ClueDataArray.Num(); i++){
		SuspectPairs.Add(TPair<int32, int32>(i, me->SummaryWidget->ClueDataArray[i].SuspectCount));
	}

	SuspectPairs.Sort([](const TPair<int32, int32>& a, const TPair<int32, int32>& b){ return a.Value > b.Value; });

	int32 SuspectTotal = 0;
	for (const auto& pair : SuspectPairs){
		SuspectTotal += pair.Value;
	}

	for (int32 i = 0; i < FMath::Min(3, SuspectPairs.Num()); i++){
		int32 ClueIdx = SuspectPairs[i].Key;
		float percent = 0;
		if (SuspectTotal > 0){
			percent = (float)SuspectPairs[i].Value / SuspectTotal * 100.0f;
		}
		switch (i){
		case 0:
			if (SuspectTextTop1 && SuspectTop1 && me->SummaryWidget->AllTexture.IsValidIndex(ClueIdx)){
				SuspectTextTop1->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), percent)));
				SuspectTop1->SetBrushFromTexture(me->SummaryWidget->AllTexture[ClueIdx]);
			}
			break;
		case 1:
			if (SuspectTextTop2 && SuspectTop2 && me->SummaryWidget->AllTexture.IsValidIndex(ClueIdx)){
				SuspectTextTop2->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), percent)));
				SuspectTop2->SetBrushFromTexture(me->SummaryWidget->AllTexture[ClueIdx]);
			}
			break;
		case 2:
			if (SuspectTextTop3 && SuspectTop3 && me->SummaryWidget->AllTexture.IsValidIndex(ClueIdx)){
				SuspectTextTop3->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), percent)));
				SuspectTop3->SetBrushFromTexture(me->SummaryWidget->AllTexture[ClueIdx]);
			}
			break;
		default:
			break;
		}
	}
}

void UStatisticsWidget::CalcWeaponRank(){
	me->SummaryWidget->LoadClueData();
	TArray<TPair<int32, int32>> WeaponPairs;
	for (int32 i = 0; i < me->SummaryWidget->ClueDataArray.Num(); i++){
		WeaponPairs.Add(TPair<int32, int32>(i, me->SummaryWidget->ClueDataArray[i].WeaponCount));
	}

	WeaponPairs.Sort([](const TPair<int32, int32>& a, const TPair<int32, int32>& b){ return a.Value > b.Value; });

	int32 WeaponTotal = 0;
	for (const auto& pair : WeaponPairs){
		WeaponTotal += pair.Value;
	}

	for (int32 i = 0; i < FMath::Min(3, WeaponPairs.Num()); i++){
		int32 ClueIdx = WeaponPairs[i].Key;
		float percent = 0;
		if (WeaponTotal > 0){
			percent = (float)WeaponPairs[i].Value / WeaponTotal * 100.0f;
		}
		switch (i){
		case 0:
			if (WeaponTextTop1 && WeaponTop1 && me->SummaryWidget->AllTexture.IsValidIndex(ClueIdx)){
				WeaponTextTop1->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), percent)));
				WeaponTop1->SetBrushFromTexture(me->SummaryWidget->AllTexture[ClueIdx]);
			}
			break;
		case 1:
			if (WeaponTextTop2 && WeaponTop2 && me->SummaryWidget->AllTexture.IsValidIndex(ClueIdx)){
				WeaponTextTop2->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), percent)));
				WeaponTop2->SetBrushFromTexture(me->SummaryWidget->AllTexture[ClueIdx]);
			}
			break;
		case 2:
			if (WeaponTextTop3 && WeaponTop3 && me->SummaryWidget->AllTexture.IsValidIndex(ClueIdx)){
				WeaponTextTop3->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), percent)));
				WeaponTop3->SetBrushFromTexture(me->SummaryWidget->AllTexture[ClueIdx]);
			}
			break;
		default:
			break;
		}
	}
}

void UStatisticsWidget::CalcMainEviRank(){
	me->SummaryWidget->LoadClueData();
	TArray<TPair<int32, int32>> MainEviPairs;
	for (int32 i = 0; i < me->SummaryWidget->ClueDataArray.Num(); i++){
		MainEviPairs.Add(TPair<int32, int32>(i, me->SummaryWidget->ClueDataArray[i].MainEvidenceCount));
	}

	MainEviPairs.Sort([](const TPair<int32, int32>& a, const TPair<int32, int32>& b){ return a.Value > b.Value; });

	int32 MainEviTotal = 0;
	for (const auto& pair : MainEviPairs){
		MainEviTotal += pair.Value;
	}

	for (int32 i = 0; i < FMath::Min(3, MainEviPairs.Num()); i++){
		int32 ClueIdx = MainEviPairs[i].Key;
		float percent = 0;
		if (MainEviTotal > 0){
			percent = (float)MainEviPairs[i].Value / MainEviTotal * 100.0f;
		}
		switch (i){
		case 0:
			if (MainEviTextTop1 && MainEviTop1 && me->SummaryWidget->AllTexture.IsValidIndex(ClueIdx)){
				MainEviTextTop1->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), percent)));
				MainEviTop1->SetBrushFromTexture(me->SummaryWidget->AllTexture[ClueIdx]);
			}
			break;
		case 1:
			if (MainEviTextTop2 && MainEviTop2 && me->SummaryWidget->AllTexture.IsValidIndex(ClueIdx)){
				MainEviTextTop2->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), percent)));
				MainEviTop2->SetBrushFromTexture(me->SummaryWidget->AllTexture[ClueIdx]);
			}
			break;
		case 2:
			if (MainEviTextTop3 && MainEviTop3 && me->SummaryWidget->AllTexture.IsValidIndex(ClueIdx)){
				MainEviTextTop3->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), percent)));
				MainEviTop3->SetBrushFromTexture(me->SummaryWidget->AllTexture[ClueIdx]);
			}
			break;
		default:
			break;
		}
	}
}

void UStatisticsWidget::CalcSpecialRank(){
	me->SummaryWidget->LoadClueData();
	TArray<TPair<int32, int32>> SpecialPairs;
	for (int32 i = 0; i < me->SummaryWidget->ClueDataArray.Num(); i++){
		SpecialPairs.Add(TPair<int32, int32>(i, me->SummaryWidget->ClueDataArray[i].SpecialThingCount));
	}

	SpecialPairs.Sort([](const TPair<int32, int32>& a, const TPair<int32, int32>& b){ return a.Value > b.Value; });

	int32 SpecialTotal = 0;
	for (const auto& pair : SpecialPairs){
		SpecialTotal += pair.Value;
	}

	for (int32 i = 0; i < FMath::Min(3, SpecialPairs.Num()); i++){
		int32 ClueIdx = SpecialPairs[i].Key;
		float percent = 0;
		if (SpecialTotal > 0){
			percent = (float)SpecialPairs[i].Value / SpecialTotal * 100.0f;
		}
		switch (i){
		case 0:
			if (SpecialTextTop1 && SpecialTop1 && me->SummaryWidget->AllTexture.IsValidIndex(ClueIdx)){
				SpecialTextTop1->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), percent)));
				SpecialTop1->SetBrushFromTexture(me->SummaryWidget->AllTexture[ClueIdx]);
			}
			break;
		case 1:
			if (SpecialTextTop2 && SpecialTop2 && me->SummaryWidget->AllTexture.IsValidIndex(ClueIdx)){
				SpecialTextTop2->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), percent)));
				SpecialTop2->SetBrushFromTexture(me->SummaryWidget->AllTexture[ClueIdx]);
			}
			break;
		case 2:
			if (SpecialTextTop3 && SpecialTop3 && me->SummaryWidget->AllTexture.IsValidIndex(ClueIdx)){
				SpecialTextTop3->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), percent)));
				SpecialTop3->SetBrushFromTexture(me->SummaryWidget->AllTexture[ClueIdx]);
			}
			break;
		default:
			break;
		}
	}
}

void UStatisticsWidget::OnClickedExit(){
	SetVisibility(ESlateVisibility::Hidden);
	auto* pc = Cast<ASherlockPlayerController>(GetOwningPlayer());
	if(me && me->LoadingUI){
		me->LoadingUI->SetVisibility(ESlateVisibility::Visible);
	}
	pc->SetShowMouseCursor(false);
	pc->SetInputMode(FInputModeGameOnly());
	GetWorld()->ServerTravel("/Game/TJ/Main?Listen", true);
}
