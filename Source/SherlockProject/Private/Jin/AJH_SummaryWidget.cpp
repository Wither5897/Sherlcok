// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_SummaryWidget.h"

#include <string>

#include "Components/Button.h"
#include "SK/InventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "AJH_SherlockGameInstance.h"
#include "Engine/Engine.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "SK/MultiPlayerState.h"

void UAJH_SummaryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	me = Cast<ATP_ThirdPersonCharacter>(GetOwningPlayer()->GetCharacter());
	if ( !me ) {
		return;
	}
	InventoryUI = me->InventoryUI;

	auto* gi = Cast<UAJH_SherlockGameInstance>(GetGameInstance());
	FString PlayerName = gi->UserNickName;

	auto* ps = Cast<AMultiPlayerState>(me->GetPlayerState());
	if ( ps->GetPlayerId() == 0 ) {
		// Player1Name->SetText(FText::FromString(PlayerName));
	}
	else if ( ps->GetPlayerId() == 1 ) {
		// Player2Name->SetText(FText::FromString(PlayerName));
	}
	else if ( ps->GetPlayerId() == 2 ) {
		// Player3Name->SetText(FText::FromString(PlayerName));
	}

	if ( Btn_Submit )
	{
		Btn_Submit->OnClicked.AddDynamic(this, &UAJH_SummaryWidget::OnMyBtn_Click);
	}
	LoadClueData();
}

void UAJH_SummaryWidget::OnSuspectImage(class UTexture2D* SavedTexture)
{
	if ( !Img_SuspectImage ) {
		return;
	}
	Img_SuspectImage->SetBrushFromTexture(SavedTexture);
	
}

void UAJH_SummaryWidget::OnWeaponImage(class UTexture2D* SavedTexture)
{
	if ( !Img_WeaponImage ) {
		return;
	}
	Img_WeaponImage->SetBrushFromTexture(SavedTexture);
}

void UAJH_SummaryWidget::OnMainEvidenceImage(class UTexture2D* SavedTexture)
{
	if ( !Img_MainEvidenceImage ) {
		return;
	}
	Img_MainEvidenceImage->SetBrushFromTexture(SavedTexture);
}

void UAJH_SummaryWidget::OnSpecialThingImage(class UTexture2D* SavedTexture)
{
	if ( !Img_SpecialThingImage ) {
		return;
	}
	Img_SpecialThingImage->SetBrushFromTexture(SavedTexture);
}

void UAJH_SummaryWidget::OnMyBtn_Click(){
	// alltexture 배열을 순회하면서 비교합니다
	for (int32 i = 0; i < AllTexture.Num(); i++)
	{
		// 다음 Clue의 인덱스 계산 (마지막 텍스처인 경우 처리)
		int32 nextClueIndex = (i + 1) % AllTexture.Num();
        
		// 각 이미지와 현재 alltexture 요소를 비교하고, 일치하면 다음 Clue의 해당 카테고리 카운트를 증가
		if (Img_SuspectImage->GetBrush().GetResourceObject() == AllTexture[i])
		{
			ClueDataArray[nextClueIndex].SuspectCount++;
		}
        
		if (Img_WeaponImage->GetBrush().GetResourceObject() == AllTexture[i])
		{
			ClueDataArray[nextClueIndex].WeaponCount++;
		}
        
		if (Img_MainEvidenceImage->GetBrush().GetResourceObject() == AllTexture[i])
		{
			ClueDataArray[nextClueIndex].MainEvidenceCount++;
		}
        
		if (Img_SpecialThingImage->GetBrush().GetResourceObject() == AllTexture[i])
		{
			ClueDataArray[nextClueIndex].SpecialThingCount++;
		}
	}
}

void UAJH_SummaryWidget::LoadClueData(){
	// JSON 파일 경로 설정
	FString JsonFilePath = FPaths::ProjectContentDir() / TEXT("Clue.json");
	FString JsonString;

	// JSON 파일 읽기
	if (FFileHelper::LoadFileToString(JsonString, *JsonFilePath))
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			// "data" 배열 가져오기
			TArray<TSharedPtr<FJsonValue>> DataArray = JsonObject->GetArrayField(TEXT("data"));

			// ClueDataArray 초기화
			ClueDataArray.Empty();

			// 각 데이터 항목을 파싱하여 ClueDataArray에 추가
			for (auto& JsonValue : DataArray)
			{
				TSharedPtr<FJsonObject> ClueObject = JsonValue->AsObject();
				FClueData ClueData;

				ClueData.ClueID = ClueObject->GetStringField(TEXT("ClueID"));
				ClueData.SuspectCount = FCString::Atoi(*ClueObject->GetStringField(TEXT("SuspectCount")));
				ClueData.WeaponCount = FCString::Atoi(*ClueObject->GetStringField(TEXT("WeaponCount")));
				ClueData.MainEvidenceCount = FCString::Atoi(*ClueObject->GetStringField(TEXT("MainEvidenceCount")));
				ClueData.SpecialThingCount = FCString::Atoi(*ClueObject->GetStringField(TEXT("SpecialThingCount")));

				ClueDataArray.Add(ClueData);
			}

			// 데이터 로드 확인을 위한 디버그 출력
			UE_LOG(LogTemp, Warning, TEXT("Successfully loaded %d clue entries"), ClueDataArray.Num());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON data"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load JSON file from path: %s"), *JsonFilePath);
	}
}
